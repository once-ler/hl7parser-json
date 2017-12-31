#pragma once

#include <regex>
#include "rxweb.hpp"
#include "server.hpp"
#include "hl7parser-rxweb/src/model/hl7MessageModel.hpp"
// #include "store.models/src/extensions.hpp"
#include "store.storage.mongo/src/mongo_client.hpp"
#include "hl7parser-cpp/src/HL7Message.hpp"

using namespace hl7parsercpp;
using namespace hl7parserrxweb::model;
using namespace store::extensions;

using json = nlohmann::json;

namespace hl7parserrxweb::middleware {
  
  template<typename S>
  rxweb::middleware<S> patientMiddleware(rxweb::server<S>& server, const string& environment, const json& config_j) {
    using Mongoclient = store::storage::mongo::MongoClient<HL7MessageModel>;
    regex isADT("^ADT", regex_constants::icase | regex_constants::ECMAScript);

    auto config_pt = make_shared<json>(config_j);
    auto uri = getPathValueFromJson(config_pt, "mongo", environment, "uri");
    auto database = getPathValueFromJson(config_pt, "mongo", environment, "database");
    
    return {
      [&isADT](const rxweb::task<S>& t) { return regex_match(t.type, isADT); },
      [&](const rxweb::task<S>& t) {
        HL7MessageModel o = *(t.data);
        // Project PID to custom Patient object.
        HL7Message hl7m{o.message};
        auto patient = hl7m.patient();
        auto pid_id = patient->patientId();
        auto patient_j = patient->toJson();
        patient_j["_id"] = pid_id;
        patient_j["mrn"] = pid_id;
    
        // Persist patient object to mongo.
        try {
          Mongoclient client(uri, database, "patient");
          auto b = client.makeBsonFromJson(patient_j);
          auto rc = client.upsertOne(b1->view(), pid_id);
          // Log?
        } catch (std::exception e) {
          // Log
        }
      }
    };
  }
}
