#pragma once

#include <iostream>
#include "json.hpp"

#include "PhoneNumberHome.hpp"

using namespace std;
using json = nlohmann::json;

namespace hl7parserJson::model::PID {

  struct PatientIdentification {
    json hl7AsJson;  

    PatientIdentification(const json& hl7AsJson_) : hl7AsJson(hl7AsJson_) {}

    void phoneNumberHome() {
      auto j0 = hl7AsJson.at("PID");
      
      cout << j0.dump() << endl;

      if (!j0.is_array() || j0.size() < 13 || j0.at(12).is_null())
        return;

      auto j1 = j0.at(12).at("Repetition");

      cout << j1.dump() << endl;

      // vector<vector<string>> v;

      for (auto& el : j1.items()) {
        auto c = el.value().at("Component");

        if (!c.is_array())
          continue;

        size_t len = c.size();
        PhoneNumberHome ph;
        for (int i = 0; i < len; i++) {
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

        
        std::cout << el.key() << " : " << c.dump() << "\n";
        // vector<string> v1 = c.at("Component");
        // v.push_back(v1);
      }

    }

  // private:
    

  };

}
