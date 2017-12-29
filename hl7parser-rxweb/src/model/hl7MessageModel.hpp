#pragma once

#include "json.hpp"

using json = nlohmann::json;

namespace hl7parserrxweb::model {
  struct HL7MessageModel {
    string message;
  };

  void to_json(json& j, const HL7MessageModel& p) {
    j = json{ { "message", p.message } };
  }

  void from_json(const json& j, HL7MessageModel& p) {
    p.message = j.value("message", "");
  }
}
