#pragma once

#include "rxweb.hpp"
#include "server.hpp"

using json = nlohmann::json;
using WebTask = rxweb::task<SimpleWeb::HTTP>;
using SocketType = SimpleWeb::ServerBase<SimpleWeb::HTTP>;

namespace hl7parserrxweb::route {
  template<typename T>
  rxweb::Route<T> persistenceRoute(rxweb::server<T>& server, const json& config_j) {    
    return {
      "/hl7",
      "POST",
      [&](std::shared_ptr<SocketType::Response> response, std::shared_ptr<SocketType::Request> request) {
        auto sub = server.getSubject();
        auto t = WebTask{ request, response };
        t.type = "PERSIST_HL7MESSAGE";
        t.data = make_shared<json>(config_j);
        sub.subscriber().on_next(t);
      }
    };
  }
}
