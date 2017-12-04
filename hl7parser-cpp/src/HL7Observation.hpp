#pragma once

#include "HL7Base.hpp"
#include <hl7parser/seg_obx.h>

namespace hl7parsercpp {
  class HL7Observation : public HL7Base {
  public:
    HL7Observation(HL7_Message* message_, int segmentPosition_) : HL7Base(message_, "OBX", segmentPosition_) {}
    
    vector<string> observationValues() {
      vector<string> vals;
      HL7_Element* el;
      string m;
      // el = hl7_obx_observation_value_text(&segment);
      // Same as: el = hl7_segment_field(&segment, 4);
      m = getString(hl7_obx_observation_value_text);
      if (m.size() > 0) {
        vals.push_back(move(m));
      } else {
        // el = hl7_obx_observation_value(&segment);
        // Same as: el = hl7_segment_component(&segment, 4, 0);
        auto results = getComponents(&segment, 4);
        vals = move(results);
      }
      return vals;
    }
  };
}
