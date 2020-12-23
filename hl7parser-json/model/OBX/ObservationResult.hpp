#pragma once

#include <iostream>
#include "json.hpp"
#include "ObservationIdentifier.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::OBX {
  struct ObservationResult {
    string _1_SetID;	
    string _2_ValueType;    
    ObservationIdentifier _3_ObservationId;    
    vector<string> _5_ObservationValue;
  };

  void to_json(json& j, const ObservationResult& p) {
    j = json{
      { "_1_SetID", p._1_SetID },
      { "_2_ValueType", p._2_ValueType },
      { "_3_ObservationId", p._3_ObservationId },
      { "_5_ObservationValue", p._5_ObservationValue }
    };
  }

  void from_json(const json& j, ObservationResult& p) {
    p._1_SetID = j.value("_1_SetID", "");
    p._2_ValueType = j.value("_2_ValueType", "");
    p._3_ObservationId = j.value("_3_ObservationId", ObservationIdentifier{});
    p._5_ObservationValue = j.value("_5_ObservationValue", vector<string>{});
  }
}
