#pragma once

#include <iostream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::OBX {
  struct ObservationIdentifier {
    string _1_Identifier;	
    string _2_Text;
    string _3_NameOfCodingSystem;
    string _4_AlternateIdentifier;
    string _5_AlternateText;
    string _6_NameOfAlternateCodingSystem;
  };

  void to_json(json& j, const ObservationIdentifier& p) {
    j = json{
      { "_1_Identifier", p._1_Identifier },
      { "_2_Text", p._2_Text },
      { "_3_NameOfCodingSystem", p._3_NameOfCodingSystem },
      { "_4_AlternateIdentifier", p._4_AlternateIdentifier },
      { "_5_AlternateText", p._5_AlternateText },
      { "_6_NameOfAlternateCodingSystem", p._6_NameOfAlternateCodingSystem }
    };
  }

  void from_json(const json& j, ObservationIdentifier& p) {
    p._1_Identifier = j.value("_1_Identifier", "");
    p._2_Text = j.value("_2_Text", "");
    p._3_NameOfCodingSystem = j.value("_3_NameOfCodingSystem", "");
    p._4_AlternateIdentifier = j.value("_4_AlternateIdentifier", "");
    p._5_AlternateText = j.value("_5_AlternateText", "");
    p._6_NameOfAlternateCodingSystem = j.value("_6_NameOfAlternateCodingSystem", "");
  }

}
