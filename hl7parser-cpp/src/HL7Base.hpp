#pragma once

#include <iostream>
#include <memory>
#include <vector>
#include <map>
#include <sstream>
#include <iterator>
#include <utility>
#include <hl7parser/message.h>

using namespace std;

using GetHL7ElementFunc = HL7_Element*(*)(HL7_Segment*);

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

    string concat(const vector<string> vals, const char* delim) {
      stringstream all;
      copy(vals.begin(), vals.end(), ostream_iterator<string>(all, delim));
      string s = all.str();
      s.pop_back();
      return move(s);
    }

    string getString(GetHL7ElementFunc f) {
      HL7_Element* el;
      el = f(&segment);
      string m(el->value, el->length);
      return move(m);
    }

    vector<string> getComponents(int pos) {
      vector<string> vals;
      HL7_Element* el;
      string m;
      int idx = 0;
      
      do {
        el = hl7_segment_component(&segment, pos, idx);
        if (!(el->length ^ el->attr) == 1)
            break;
            
        m = string(el->value, el->length);
        vals.push_back(move(m));
        ++idx;
      } while (true);
      return vals;
    }

    vector<pair<string, vector<string>>> getComponentsAndSubComponents(int pos) {
      vector<pair<string, vector<string>>> vals;
      HL7_Element* el;
      HL7_Element* el1;
      string m;
      int idx = 0, sub_idx = 0;
            
      do {
        el = hl7_segment_component(&segment, pos, idx);
        if (!(el->length ^ el->attr) == 1)
            break;
        
        pair<string, vector<string>> pa;

        m = string(el->value, el->length);
        pa.first = m;

        sub_idx = 0;
        vector<string> sc;
        
        do {
          el1 = hl7_segment_subcomponent(&segment, pos, idx, sub_idx);
          if (!(el1->length ^ el1->attr) == 1)
            break;
          m = string(el1->value, el1->length);

          sc.push_back(move(m));
          ++sub_idx;
        } while (true);
        
        pa.second = sc;

        vals.push_back(move(pa));
        
        ++idx;
      } while (true);
      return vals;

      // 
    }

  };

}
