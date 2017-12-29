#pragma once

#include "rxweb.hpp"
#include "server.hpp"

namespace hl7parserrxweb::test {

  json config_j = {
    {
      "hl7", {
        { "port", 1717 },
        { "threads", 20 }
      }
    },
    { "mongo", {
        { "development", {
            { "uri", "" },
            { "database", "" }
          }
        },
        { "staging", {
            { "uri", "mongodb://127.0.0.1:27017" },
            { "database", "test" }
          }
        },
        { "prod", {
            { "uri", "" },
            { "database", "" }
          }
        }
      }
    }
  };

  int start(const string& environment, const json& config_j) {
    int port = config_j.value("/hl7/port"_json_pointer, 1717);
    int threads = config_j.value("/hl7/threads"_json_pointer, 1);

    rxweb::server<SimpleWeb::HTTP> server(port, threads);

    server.onNext = epic::interconnect::integration::finalMiddleware(server);

    server.routes = {
      persistenceRoute(server, config_j)
    };

    server.middlewares = {
      persistenceMiddleware(server, environment, config_j)
    };

    std::thread server_thread([&server]() {
      server.start();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    spdlog::get("logger")->info() << "[epic-interconnect]" << " started. environment: " << environment << ", port: " << port << ", threads: " << threads;
    durian::flushLog();

    server_thread.join();
  }

}
