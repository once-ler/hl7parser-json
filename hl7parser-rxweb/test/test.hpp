#pragma once

#ifndef HL7PARSER_DLL
#define HL7PARSER_DLL
#endif

#include "client_http.hpp"
#include "rxweb.hpp"
#include "server.hpp"
#include "hl7parser-rxweb/src/middleware/finalMiddleware.hpp"
#include "hl7parser-rxweb/src/middleware/persistenceMiddleware.hpp"
#include "hl7parser-rxweb/src/middleware/patientMiddleware.hpp"
#include "hl7parser-rxweb/src/middleware/observationMiddleware.hpp"
#include "hl7parser-rxweb/src/route/persistenceRoute.hpp"

namespace hl7parserrxweb::test {

  int start(const string& environment, const json& config_j) {
    int port = config_j.value("/hl7/port"_json_pointer, 1717);
    int threads = config_j.value("/hl7/threads"_json_pointer, 1);

    rxweb::server<SimpleWeb::HTTP> server(port, threads);

    server.onNext = hl7parserrxweb::middleware::finalMiddleware(server);

    server.routes = {
      hl7parserrxweb::route::persistenceRoute(server, config_j)
    };

    server.middlewares = {
      hl7parserrxweb::middleware::persistenceMiddleware(server, environment, config_j),
      hl7parserrxweb::middleware::patientMiddleware(server, environment, config_j),
      hl7parserrxweb::middleware::observationMiddleware(server, environment, config_j)
    };

    std::thread server_thread([&server]() {
      server.start();
    });

    std::this_thread::sleep_for(std::chrono::seconds(1));

    // spdlog::get("logger")->info() << "[epic-interconnect]" << " started. environment: " << environment << ", port: " << port << ", threads: " << threads;
    // durian::flushLog();

    server_thread.join();
  }

}
