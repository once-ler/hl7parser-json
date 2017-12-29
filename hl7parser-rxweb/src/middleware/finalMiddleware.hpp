#pragma once

#include "rxweb.hpp"
#include "server.hpp"

using json = nlohmann::json;

// Final Handler
namespace hl7parserrxweb::middleware {
  template<typename T>
  rxweb::middleware<T> finalMiddleware(rxweb::server<T>& server) {
    
    return {
      [](const rxweb::task<T>& t)->bool { return (t.type == "HL7ACK_RESPONSE"); },
      [](const rxweb::task<T>& t) {
        auto res = t.data->value("response"_json_pointer, "");
        *(t.response) << "HTTP/1.1 200 OK\r\nContent-Length: " << res.size() << "\r\n\r\n" << res;
      }
    };
  }
}
