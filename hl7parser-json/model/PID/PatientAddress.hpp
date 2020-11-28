#pragma once

#include <iostream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::PID {
  struct PatientAddress {
    string _1_StreetAddress;	
    string _2_OtherDesignation;	
    string _3_City;	
    string _4_StateOrProvince;
    string _5_ZipOrPostalCode;		
    string _6_Country;		
    string _7_AddressType;		
    string _8_OtherGeographicDesignation;		
    string _9_CountyParishCode;
    string _10_CensusTract;
    string _11_AddressRepresentationCode;
    string _12_AddressValidityRange;
  };

  void to_json(json& j, const PatientAddress& p) {
    j = json{
      { "_1_StreetAddress", p._1_StreetAddress },
      { "_2_OtherDesignation", p._2_OtherDesignation },
      { "_3_City", p._3_City },
      { "_4_StateOrProvince", p._4_StateOrProvince },
      { "_5_ZipOrPostalCode", p._5_ZipOrPostalCode },
      { "_6_Country", p._6_Country },
      { "_7_AddressType", p._7_AddressType },
      { "_8_OtherGeographicDesignation", p._8_OtherGeographicDesignation },
      { "_9_CountyParishCode", p._9_CountyParishCode },
      { "_10_CensusTract", p._10_CensusTract },
      { "_11_AddressRepresentationCode", p._11_AddressRepresentationCode },
      { "_12_AddressValidityRange", p._12_AddressValidityRange }
    };
  }

  void from_json(const json& j, PatientAddress& p) {
    p._1_StreetAddress = j.value("_1_StreetAddress", "");
    p._2_OtherDesignation = j.value("_2_OtherDesignation", "");
    p._3_City = j.value("_3_City", "");
    p._4_StateOrProvince = j.value("_4_StateOrProvince", "");
    p._5_ZipOrPostalCode = j.value("_5_ZipOrPostalCode", "");
    p._6_Country = j.value("_6_Country", "");
    p._7_AddressType = j.value("_7_AddressType", "");
    p._8_OtherGeographicDesignation = j.value("_8_OtherGeographicDesignation", "");
    p._9_CountyParishCode = j.value("_9_CountyParishCode", "");
    p._10_CensusTract = j.value("_10_CensusTract", "");
    p._11_AddressRepresentationCode = j.value("_11_AddressRepresentationCode", "");
    p._12_AddressValidityRange = j.value("_12_AddressValidityRange", "");
  }
}
