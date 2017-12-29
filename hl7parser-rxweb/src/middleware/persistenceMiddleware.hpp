#pragma once

#include "rxweb.hpp"
#include "server.hpp"
#include "extensions.hpp"
#include "model/hl7MessageModel.hpp"
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
          string streamType = hl7m.streamType();

          HL7MessageModel hl7_j{ content };          
          json j = hl7_j;

          // Persist event.
          client.events.SaveOne(streamType, j);

          // Emit acknowledgment.
          auto ackMessage = hl7m.acknowledgment();

          auto cptask = t;
          *(cptask.data) = ackMessage;
          cptask.type = "HL7ACK_RESPONSE";
          server.getSubject().subscriber().on_next(cptask);

          // More tasks to emit...

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
