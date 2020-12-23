#pragma once

#include <iostream>
#include "json.hpp"

#include "ObservationResult.hpp"
#include "ObservationIdentifier.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::OBX { 

  class Observation {
    json hl7AsJson;
    shared_ptr<vector<ObservationResult>> observationResults = nullptr;

public:
    Observation(const json& hl7AsJson_) : hl7AsJson(hl7AsJson_) {}
   
    shared_ptr<vector<ObservationResult>> getObservationResults() {
      if (observationResults != nullptr)
        return observationResults;

      observationResults = make_shared<vector<ObservationResult>>();

      auto j0 = hl7AsJson.at("OBX");

      if (!j0.is_array())
        return observationResults;

      for (auto& c : j0) {
        if (!c.is_array())
          continue;

        size_t len = c.size();
        ObservationResult obxr;
        for (size_t i = 0; i < len; i++) {
          // 
          switch (i) {
            case 0:
              obxr._1_SetID = c.at(i).is_null() ? "" : c.at(i).get<string>();
              break;
            case 1:
              obxr._2_ValueType = c.at(i).is_null() ? "" : c.at(i).get<string>();
              break;
            case 2: 
              obxr._3_ObservationId = getObservationIdentifier(c.at(i));
              break;
            case 4:
              obxr._5_ObservationValue = getObservationValue(c.at(i));
              break;
            default:
            break;
          }
        }     

        observationResults->push_back(obxr);
      }

      return observationResults;
    }

private:
    vector<string> getObservationValue(const json& j) {
      vector<string> vals;
      
      auto j1 = j.value("/Repetition"_json_pointer, json({}));

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
        for (size_t i = 0; i < len; i++) {
          auto v = c.at(i).is_null() ? "" : c.at(i).get<string>();
          vals.push_back(v);
        }
      }

      return vals;
    }

    ObservationIdentifier getObservationIdentifier(const json& j) {
      ObservationIdentifier oid;
      
      auto j1 = j.value("/Repetition"_json_pointer, json({}));

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
        for (size_t i = 0; i < len; i++) {
          auto v = c.at(i).is_null() ? "" : c.at(i).get<string>();
          
          switch (i) {
            case 0:
              oid._1_Identifier = v;
              break;
            case 1:
              oid._2_Text = v;
              break;
            case 2:
              oid._3_NameOfCodingSystem = v;
              break;
            case 3:
              oid._4_AlternateIdentifier = v;
              break;
            case 4:
              oid._5_AlternateText = v;
              break;
            case 5:
              oid._6_NameOfAlternateCodingSystem = v;    
              break;
            default:
              break;
          }
        }
      }

      return oid;
    }
 
  };
}
