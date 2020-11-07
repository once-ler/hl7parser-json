#pragma once

#include <iostream>

using namespace std;

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
}
