#pragma once

#include <regex>
#include "rxweb.hpp"
#include "server.hpp"
#include "hl7parser-rxweb/src/model/hl7MessageModel.hpp"
#include "hl7parser-cpp/src/HL7Message.hpp"
#include "mssql_client.hpp"
#include "models.hpp"

using namespace hl7parsercpp;
using namespace hl7parserrxweb::model;

using namespace store::extensions;
using namespace store::models;
using namespace store::storage::mssql;

using json = nlohmann::json;

namespace hl7parserrxweb::middleware {
  
  template<typename S>
  rxweb::middleware<S> observationMiddleware(rxweb::server<S>& server, const string& environment, const json& config_j) {
    regex isMDM("^MDM", regex_constants::icase | regex_constants::ECMAScript);
    
    auto config_pt = make_shared<json>(config_j);
    auto host = getPathValueFromJson<string>(config_pt, "mssql", environment, "server");
    auto database = getPathValueFromJson<string>(config_pt, "mssql", environment, "database");
    auto port = getPathValueFromJson<int>(config_pt, "mssql", environment, "port");
    auto user = getPathValueFromJson<string>(config_pt, "mssql", environment, "user");
    auto password = getPathValueFromJson<string>(config_pt, "mssql", environment, "password");
    auto store = getPathValueFromJson<string>(config_pt, "universalConsent", "store");
    auto studyId = getPathValueFromJson<string>(config_pt, "universalConsent", "studyId");
    auto processState = getPathValueFromJson<string>(config_pt, "universalConsent", "processState");
    
    return {
      [&isMDM](const rxweb::task<S>& t) { return regex_match(t.type, isMDM); },
      [&](const rxweb::task<S>& t) {
        // Iterate through all OBX and lookup for positive responses.
        HL7MessageModel o = *(t.data);
        HL7Message hl7m{o.message};
        auto observations = hl7m.observations();
        bool persist = false;
        for(const auto o : observations) {
          auto vals = o->ObservationValues();     
          // Find "Y" in list of observations.
          regex ex("y", regex_constants::icase | regex_constants::ECMAScript);
          auto it = find_if(vals.begin(), vals.end(), [&ex](const auto& m)->bool { return std::regex_match(m, ex); });

          if (it != vals.end()) {
            cout << *it << endl;
            persist = true;
            break;
          }
        }
        
        // Persist patient object to SQL if any response is "Y".
        if (persist) {
          auto patient = hl7m.patient();
          auto pid_id = patient->patientId();
          auto firstName = patient->firstName();
          auto lastName = patient->lastName();
          auto dob = patient->DateTimeOfBirth();

          DBContext db_ctx("mdm", host, port, database, user, password, 30);
          
          using MsSqlClient = store::storage::mssql::MsSqlClient<IEvent>;
          MsSqlClient client(db_ctx);

          client.insertOne("epic", "participant_hist",
            {"from_store", "_uid", "start_time", "mrn", "firstName", "lastName", "dob", "processState", "streetAddressLine", "city", "state", "postalCode", "processed"},
            store, studyId, "current_timestamp", pid_id, firstName, lastName, dob, processState, "", "", "", "", 0
          );
        }

      }
    };
  }
}
