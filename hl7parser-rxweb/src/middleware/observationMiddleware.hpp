#pragma once

#include <regex>
#include "rxweb.hpp"
#include "server.hpp"
#include "hl7parser-rxweb/src/model/hl7MessageModel.hpp"
// #include "store.models/src/extensions.hpp"
// #include "store.storage.mongo/src/mongo_client.hpp"
#include "hl7parser-cpp/src/HL7Message.hpp"

using namespace hl7parsercpp;
using namespace hl7parserrxweb::model;
using namespace store::extensions;

using json = nlohmann::json;

namespace hl7parserrxweb::middleware {
  
  template<typename S>
  rxweb::middleware<S> observationMiddleware(rxweb::server<S>& server, const string& environment, const json& config_j) {
    // using Mongoclient = store::storage::mongo::MongoClient<HL7MessageModel>;
    regex isMDM("^MDM", regex_constants::icase | regex_constants::ECMAScript);
    
    return {
      [&isADT](const rxweb::task<S>& t) { return regex_match(t.type, isMDM); },
      [&](const rxweb::task<S>& t) {
        // Iterate through all OBX and lookup for positive responses.

        // Persist patient object to SQL.
      }
    };
  }
}
