#pragma once

#include <iostream>
#include "json.hpp"

#include "TranscribedDocumentInformation.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::TXA { 

  class TranscriptionDocumentHeader {
    json hl7AsJson;
    shared_ptr<TranscribedDocumentInformation> transcribedDocumentInformation = nullptr;

public:
    TranscriptionDocumentHeader(const json& hl7AsJson_) : hl7AsJson(hl7AsJson_) {}
   
    shared_ptr<TranscribedDocumentInformation> getTranscribedDocumentInformation() {
      if (transcribedDocumentInformation != nullptr)
        return transcribedDocumentInformation;

      transcribedDocumentInformation = make_shared<TranscribedDocumentInformation>();

      auto c = hl7AsJson.at("TXA").at(0);

      if (!c.is_array())
        return transcribedDocumentInformation;

      size_t len = c.size();
      for (size_t i = 0; i < len; i++) {
        
        switch (i) {
          case 1:
            transcribedDocumentInformation->_2_DocumentType = c.at(i).is_null() ? "" : c.at(i).get<string>();
            break;
          case 3:
            transcribedDocumentInformation->_4_ActivityDateTime = c.at(i).is_null() ? "" : c.at(i).get<string>();
            break;
          case 16: 
            transcribedDocumentInformation->_17_DocumentCompletionStatus = c.at(i).is_null() ? "" : c.at(i).get<string>();
            break;
          default:
          break;
        }
      }  

      return transcribedDocumentInformation;
    }
  };
}
