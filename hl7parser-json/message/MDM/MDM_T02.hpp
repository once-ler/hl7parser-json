#pragma once

#include "hl7parser-json/model/PID/PatientIdentification.hpp"
#include "hl7parser-json/model/OBX/Observation.hpp"
#include "hl7parser-json/model/TXA/TranscriptionDocumentHeader.hpp"

using namespace std;
using namespace hl7parserJson::model;

using json = nlohmann::json;

namespace hl7parserJson::message::MDM {

  class MDM_T02 {
    json hl7AsJson;
    shared_ptr<PID::PatientIdentification> patientIdentification = nullptr;
    shared_ptr<OBX::Observation> observation = nullptr;
    shared_ptr<TXA::TranscriptionDocumentHeader> transcriptionDocumentHeader = nullptr;
  public:
    MDM_T02(const json& hl7AsJson_) : hl7AsJson(hl7AsJson_) {}

    shared_ptr<PID::PatientIdentification> getPatientIdentification() {
      if (patientIdentification == nullptr)
        patientIdentification = make_shared<PID::PatientIdentification>(hl7AsJson);
        
      return patientIdentification;
    }

    shared_ptr<OBX::Observation> getObservation() {
      if (observation == nullptr)
        observation = make_shared<OBX::Observation>(hl7AsJson);
        
      return observation;
    }

    shared_ptr<TXA::TranscriptionDocumentHeader> getTranscription() {
      if (transcriptionDocumentHeader == nullptr)
        transcriptionDocumentHeader = make_shared<TXA::TranscriptionDocumentHeader>(hl7AsJson);
        
      return transcriptionDocumentHeader;
    }
  };

}
