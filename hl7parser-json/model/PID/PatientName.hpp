#pragma once

#include <iostream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::PID {
  struct PatientName {
    string _1_FamilyName;	
    string _2_GivenName;
    string _3_MiddleName;
    string _4_Suffix;
    string _5_Prefix;
    string _6_Degree;
    string _7_NameTypeCode;
    string _8_NameRepresentationCode;
    string _9_NameContext;
    string _10_NameValidityRange;
    string _11_NameAssemblyOrder;
  };

  void to_json(json& j, const PatientName& p) {
    j = json{
      { "_1_FamilyName", p._1_FamilyName },
      { "_2_GivenName", p._2_GivenName },
      { "_3_MiddleName", p._3_MiddleName },
      { "_4_Suffix", p._4_Suffix },
      { "_5_Prefix", p._5_Prefix },
      { "_6_Degree", p._6_Degree },
      { "_7_NameTypeCode", p._7_NameTypeCode },
      { "_8_NameRepresentationCode", p._8_NameRepresentationCode },
      { "_9_NameContext", p._9_NameContext },
      { "_10_NameValidityRange", p._10_NameValidityRange },
      { "_11_NameAssemblyOrder", p._11_NameAssemblyOrder }
    };
  }

  void from_json(const json& j, PatientName& p) {
    p._1_FamilyName = j.value("_1_FamilyName", "");
    p._2_GivenName = j.value("_2_GivenName", "");
    p._3_MiddleName = j.value("_3_MiddleName", "");
    p._4_Suffix = j.value("_4_Suffix", "");
    p._5_Prefix = j.value("_5_Prefix", "");
    p._6_Degree = j.value("_6_Degree", "");
    p._7_NameTypeCode = j.value("_7_NameTypeCode", "");
    p._8_NameRepresentationCode = j.value("_8_NameRepresentationCode", "");
    p._9_NameContext = j.value("_9_NameContext", "");
    p._10_NameValidityRange = j.value("_10_NameValidityRange", "");
    p._11_NameAssemblyOrder = j.value("_11_NameAssemblyOrder", "");
  }
}
