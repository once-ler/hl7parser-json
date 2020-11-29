#pragma once

#include <iostream>
#include "json.hpp"

#include "PhoneNumberHome.hpp"
#include "PatientAddress.hpp"
#include "PatientName.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::PID { 

  class PatientIdentification {
    json hl7AsJson;  
    shared_ptr<vector<PhoneNumberHome>> phoneNumberHome = nullptr;
    shared_ptr<vector<PatientAddress>> patientAddress = nullptr;
    shared_ptr<vector<PatientName>> patientName = nullptr;
    
public:
    PatientIdentification(const json& hl7AsJson_) : hl7AsJson(hl7AsJson_) {}

    shared_ptr<vector<PhoneNumberHome>> getPhoneNumberHome() {
      if (phoneNumberHome != nullptr)
        return phoneNumberHome;

      phoneNumberHome = make_shared<vector<PhoneNumberHome>>();

      auto j0 = hl7AsJson.at("PID");
      
      cout << j0.dump() << endl;

      if (!j0.is_array() || j0.size() < 13 || j0.at(12).is_null())
        return phoneNumberHome;

      auto j1 = j0.at(12).at("Repetition");

      cout << j1.dump() << endl;

      for (auto& el : j1.items()) {
        json c;
        auto b = el.value();
        if (b.is_object())
          c = b.at("Component");
        else
          c = b;

        if (!c.is_array())
          continue;

        size_t len = c.size();
        PhoneNumberHome ph;
        for (size_t i = 0; i < len; i++) {
          auto v = c.at(i).is_null() ? "" : c.at(i).get<string>();
          switch (i) {
            case 0:
              ph._1_TelephoneNumber = v;
            break;
            case 1:
              ph._2_TelecommunicationUseCode = v;
            break;
            case 2:
              ph._3_TelecommunicationEquipmentType = v;
            break;
            case 3:
              ph._4_EmailAddress = v;
            break;
            case 4:
              ph._5_CountryCode = v;
            break;
            case 5:
              ph._6_AreaCityCode = v;
            break;
            case 6:
              ph._7_PhoneNumber = v;
            break;
            case 7:
              ph._8_Extension = v;
            break;
            case 8:
              ph._9_AnyText = v;
            break;  
            default:
            break;
          }
        }

        phoneNumberHome->push_back(ph);
        
        // std::cout << el.key() << " : " << c.dump() << "\n";
      }

      return phoneNumberHome;
    }

    shared_ptr<vector<PatientAddress>> getPatientAddress() {
      if (patientAddress != nullptr)
        return patientAddress;

      patientAddress = make_shared<vector<PatientAddress>>();

      auto j0 = hl7AsJson.at("PID");
      
      if (!j0.is_array() || j0.size() < 11 || j0.at(10).is_null())
        return patientAddress;

      auto j1 = j0.at(10).at("Repetition");

      cout << j1.dump() << endl;

      for (auto& el : j1.items()) {
        json c;
        auto b = el.value();
        if (b.is_object())
          c = b.at("Component");
        else
          c = b;

        if (!c.is_array())
          continue;

        size_t len = c.size();
        PatientAddress pa;
        for (size_t i = 0; i < len; i++) {
          auto v = c.at(i).is_null() ? "" : c.at(i).get<string>();
          switch (i) {
            case 0:
              pa._1_StreetAddress = v;
            break;
            case 1:
              pa._2_OtherDesignation = v;
            break;
            case 2:
              pa._3_City = v;
            break;
            case 3:
              pa._4_StateOrProvince = v;
            break;
            case 4:
              pa._5_ZipOrPostalCode = v;
            break;
            case 5:
              pa._6_Country = v;
            break;
            case 6:
              pa._7_AddressType = v;
            break;
            case 7:
              pa._8_OtherGeographicDesignation = v;
            break;
            case 8:
              pa._9_CountyParishCode = v;
            break;
            case 9:
              pa._10_CensusTract = v;
            break;
            case 10:
              pa._11_AddressRepresentationCode = v;
            break;
            case 11:
              pa._12_AddressValidityRange = v;
            break;
            default:
            break;
          }
        }

        patientAddress->push_back(pa);
        
        // std::cout << el.key() << " : " << c.dump() << "\n";
      }

      return patientAddress;
    }

    shared_ptr<vector<PatientName>> getPatientName() {
      if (patientName != nullptr)
        return patientName;

      patientName = make_shared<vector<PatientName>>();

      auto j0 = hl7AsJson.at("PID");
      
      if (!j0.is_array() || j0.size() < 5 || j0.at(4).is_null())
        return patientName;

      auto j1 = j0.at(4).at("Repetition");

      for (auto& el : j1.items()) {
        json c;
        auto b = el.value();
        if (b.is_object())
          c = b.at("Component");
        else
          c = b;

        if (!c.is_array())
          continue;

        size_t len = c.size();
        PatientName pa;
        for (size_t i = 0; i < len; i++) {
          auto v = c.at(i).is_null() ? "" : c.at(i).get<string>();
          switch (i) {
            case 0:
              pa._1_FamilyName = v;
            break;
            case 1:
              pa._2_GivenName = v;
            break;
            case 2:
              pa._3_MiddleName = v;
            break;
            case 3:
              pa._4_Suffix = v;
            break;
            case 4:
              pa._5_Prefix = v;
            break;
            case 5:
              pa._6_Degree = v;
            break;
            case 6:
              pa._7_NameTypeCode = v;
            break;
            case 7:
              pa._8_NameRepresentationCode = v;
            break;
            case 8:
              pa._9_NameContext = v;
            break;
            case 9:
              pa._10_NameValidityRange = v;
            break;
            case 10:
              pa._11_NameAssemblyOrder = v;
            break;
            default:
            break;
          }
        }

        patientName->push_back(pa);
      }

      return patientName;
    }

    json toJson() {
      auto pn = getPhoneNumberHome();
      auto pa = getPatientAddress();
      auto pu = getPatientName();

      json pnv = *pn, pna = *pa, pnu = *pu;

      auto j = json{
        { "patientName", pnu },
        { "phoneNumberHome", pnv },
        { "patientAddress", pna }
      };

      return j;
    }

  private:
    

  };

}
