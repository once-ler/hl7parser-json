#pragma once

#include "rxweb.hpp"
#include "server.hpp"
#include "extensions.hpp"
#include "hl7parserrxweb_common.hpp"
#include "mongo_base_client.hpp"
#include "HL7Util.hpp"

using namespace hl7parserrxweb::common;
using namespace store::extensions;
using namespace hl7parsercpp::util;

using json = nlohmann::json;

namespace hl7parserrxweb::middleware {
  
  template<typename S>
  rxweb::middleware<S> persistenceMiddleware(rxweb::server<S>& server, const string& environment, const json& config_j) {
    using Mongoclient = store::storage::mongo::MongoClient<S>;
    
    return {
      [](const rxweb::task<S>& t)->bool { return (t.type == "PERSIST_HL7MESSAGE"); },
      [&](const rxweb::task<S>& t) {
        auto uri = getPathValueFromJson(config_j, "mongo", environment, "uri");
        auto database = getPathValueFromJson(config_j, "mongo", environment, "database");

        try {
          Mongoclient client(uri, database, "hl7x");

          // Extract message from request body.
          auto content = t.request->content.string();

          HL7Message hl7m{content};

          // Parse message to get PID Identifier.
          auto patient = hl7m.patient();
          auto pid_id = patient.patientId();

          // Get the message event type.
          auto header = hl7m.header();
          auto hm = header->Header();
          auto msg_type = hl7m.toComponentString(header->MessageType());
    
          HL7EventModel hl7_j;
          hl7_j.data = content;

          json j = hl7_j;

          string streamType = concat(msg_type, ":", pid_id);

          // Persist event.
          client.events.SaveOne(streamType, j);

        } catch(const SimpleWeb::system_error& e) {
          resp = {
            { "error", e.what() }
          };
        } catch (std::exception e) {
          resp = {
            { "error", e.what() }
          };
        }

      }
    };
    
  }
}
