#pragma once

#include <iostream>

using namespace std;

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

}