#pragma once

#include <iostream>
#include "json.hpp"

using namespace std;

using json = nlohmann::json;

namespace hl7parserJson::model::TXA {
  struct TranscribedDocumentInformation {
    string _2_DocumentType;
    string _4_ActivityDateTime;
    string _17_DocumentCompletionStatus;
  };

  void to_json(json& j, const TranscribedDocumentInformation& p) {
    j = json{
      { "_2_DocumentType", p._2_DocumentType },
      { "_4_ActivityDateTime", p._4_ActivityDateTime },
      { "_17_DocumentCompletionStatus", p._17_DocumentCompletionStatus }
    };
  }

  void from_json(const json& j, TranscribedDocumentInformation& p) {
    p._2_DocumentType = j.value("_2_DocumentType", "");
    p._4_ActivityDateTime = j.value("_4_ActivityDateTime", "");
    p._17_DocumentCompletionStatus = j.value("_17_DocumentCompletionStatus", "");
  }

}
