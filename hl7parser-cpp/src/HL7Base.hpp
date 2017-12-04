#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <hl7parser/message.h>

using namespace std;

typedef HL7_Element* GetHL7ElementFunc(HL7_Segment*);

namespace hl7parsercpp {
  class HL7Base {
  public:
    HL7Base(HL7_Message* message_, const string& segmentId_, int segmentPosition_) : message(message_), segmentId(segmentId_), segmentPosition(segmentPosition_) {
      hl7_message_segment(message, &segment, segmentId.c_str(), segmentPosition);
    }
  protected:
    HL7_Message* message;
    HL7_Segment segment;
    string segmentId;
    int segmentPosition = 0;

    string getString(GetHL7ElementFunc f) {
      HL7_Element* el;
      el = f(&segment);
      string m(el->value, el->length);
      return move(m);
    }

    vector<string> getComponents(HL7_Segment* segment, int pos) {
      vector<string> vals;
      HL7_Element* el;
      string m;
      int idx = 0;
      
      do {
        el = hl7_segment_component(segment, pos, idx);
        m = string(el->value, el->length);
        vals.push_back(move(m));
        ++idx;
      } while (el->length > 0 || el->attr > 0);
      return vals;
    }
  };

}
