#pragma once

#include "rxweb.hpp"
#include "server.hpp"
#include "hl7parser-rxweb/src/model/hl7MessageModel.hpp"
#include "store.models/src/extensions.hpp"
#include "store.storage.mongo/src/mongo_client.hpp"
#include "hl7parser-cpp/src/HL7Message.hpp"

using namespace hl7parsercpp;
using namespace hl7parserrxweb::model;
using namespace store::extensions;

using json = nlohmann::json;

namespace hl7parserrxweb::middleware {
  
  template<typename S>
  rxweb::middleware<S> persistenceMiddleware(rxweb::server<S>& server, const string& environment, const json& config_j) {
    using Mongoclient = store::storage::mongo::MongoClient<HL7MessageModel>;
    
    return {
      [](const rxweb::task<S>& t)->bool { return (t.type == "PERSIST_HL7MESSAGE"); },
      [&](const rxweb::task<S>& t) {
        auto config_pt = make_shared<json>(config_j);
        auto uri = getPathValueFromJson(config_pt, "mongo", environment, "uri");
        auto database = getPathValueFromJson(config_pt, "mongo", environment, "database");
        json resp;
        
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

          // Acknowledgment.
          resp = {{ "response", hl7m.acknowledgment() }};
          
          auto nextTask = t;
          *(nextTask.data) = j;
          nextTask.type = streamType;
          server.getSubject().subscriber().on_next(nextTask);
          // More tasks to emit...          
        } catch(const SimpleWeb::system_error& e) {
          resp = {{ "response", e.what() }};
        } catch (std::exception e) {
          resp = {{ "response", e.what() }};
        }

        auto cptask = t;
        *(cptask.data) = resp;
        cptask.type = "HL7ACK_RESPONSE";
        server.getSubject().subscriber().on_next(cptask);
        
      }
    };
    
  }
}
