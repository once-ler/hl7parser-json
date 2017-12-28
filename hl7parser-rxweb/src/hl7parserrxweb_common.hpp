#pragma once

#include "json.hpp"
#include "models.hpp"

using namespace store::models;

using json = nlohmann::json;

namespace hl7parserrxweb::common {
  struct HL7EventModel : Model {
    using Model::Model;
    string data;
  };

  void to_json(json& j, const HL7EventModel& p) {
    j = json{ { "id", p.id }, { "data", p.data } };
  }

  void from_json(const json& j, HL7EventModel& p) {
    p.id = j.value("id", "");
    p.data = j.value("data", "");
  }
}
