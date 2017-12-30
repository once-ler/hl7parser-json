#pragma once

#include "HL7Base.hpp"
#include <hl7parser/seg_pid.h>

namespace hl7parsercpp {
  class HL7Patient : public HL7Base {
  public:
    
    HL7Patient(HL7_Message* message_) : HL7Base(message_, "PID", 0) {}
    
    string patientId() {
      return getString(hl7_pid_patient_id);
    }
    string firstName() {
      return getString(hl7_pid_first_name);
    }
    string lastName() {
      return getString(hl7_pid_last_name);
    }

    vector<string> PatientIdentifierList() {
      auto results = getComponents(2);
      return move(results);
    }

    vector<pair<string, vector<string>>> PatientIdentifierListX() {
      auto results = getComponentsAndSubComponents(2);
      return move(results);
    }

    vector<string> PatientName() {
      auto results = getComponents(4);
      return move(results);
    }

    string DateTimeOfBirth() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 6);
      });
    }

    string AdministrativeSex() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 7);
      });
    }

    vector<string> Race() {
      auto results = getComponents(9);
      return move(results);
    }

    // XAD Component Type
    // http://hl7-definition.caristix.com:9010/Default.aspx?version=HL7%20v2.5.1&dataType=XAD
    vector<string> PatientAddress() {
      auto results = getComponents(10);
      return move(results);
    }

    // XTN Component Type
    // http://hl7-definition.caristix.com:9010/Default.aspx?version=HL7%20v2.5.1&dataType=XTN
    vector<string> PhoneNumberHome() {
      auto results = getComponents(12);
      return move(results);
    }

    vector<string> EthnicGroup() {
      auto results = getComponents(21);
      return move(results);
    }

    vector<pair<string, string>> Patient() {
      return {
        { "PatientIdentifierList", join(PatientIdentifierList(), "^") },
        { "PatientName", join(PatientName(), "^") },
        { "DateTimeOfBirth", DateTimeOfBirth() },
        { "AdministrativeSex", AdministrativeSex() },
        { "Race", join(Race(), "^") },
        { "PatientAddress", join(PatientAddress(), "^") },
        { "PhoneNumberHome", join(PhoneNumberHome(), "^") },
        { "EthnicGroup", join(EthnicGroup(), "^") }
      };
    }

    json toJson() {
      return move(HL7Base::toJson(Patient()));
    }

  };
}
