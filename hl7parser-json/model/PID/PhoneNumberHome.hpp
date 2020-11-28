#pragma once

#include <iostream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::PID {

  struct PhoneNumberHome {
    string _1_TelephoneNumber;	
    string _2_TelecommunicationUseCode;	
    string _3_TelecommunicationEquipmentType;	
    string _4_EmailAddress;
    string _5_CountryCode;		
    string _6_AreaCityCode;		
    string _7_PhoneNumber;		
    string _8_Extension;		
    string _9_AnyText;
  };

  void to_json(json& j, const PhoneNumberHome& p) {
    j = json{
      { "_1_TelephoneNumber", p._1_TelephoneNumber },
      { "_2_TelecommunicationUseCode", p._2_TelecommunicationUseCode },
      { "_3_TelecommunicationEquipmentType", p._3_TelecommunicationEquipmentType },
      { "_4_EmailAddress", p._4_EmailAddress },
      { "_5_CountryCode", p._5_CountryCode },
      { "_6_AreaCityCode", p._6_AreaCityCode },
      { "_7_PhoneNumber", p._7_PhoneNumber },
      { "_8_Extension", p._8_Extension },
      { "_9_AnyText", p._9_AnyText }
    };
  }

  void from_json(const json& j, PhoneNumberHome& p) {
    p._1_TelephoneNumber = j.value("_1_TelephoneNumber", "");
    p._2_TelecommunicationUseCode = j.value("_2_TelecommunicationUseCode", "");
    p._3_TelecommunicationEquipmentType = j.value("_3_TelecommunicationEquipmentType", "");
    p._4_EmailAddress = j.value("_4_EmailAddress", "");
    p._5_CountryCode = j.value("_5_CountryCode", "");
    p._6_AreaCityCode = j.value("_6_AreaCityCode", "");
    p._7_PhoneNumber = j.value("_7_PhoneNumber", "");
    p._8_Extension = j.value("_8_Extension", "");
    p._9_AnyText = j.value("_9_AnyText", "");
  }
}