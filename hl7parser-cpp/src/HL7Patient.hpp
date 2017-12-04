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
    vector<string> patientIdentifierList() {
      auto results = getComponents(&segment, 2);
      return move(results);
    }
  };
}
