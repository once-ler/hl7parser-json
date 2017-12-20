#pragma once

#include "HL7Base.hpp"
#include <hl7parser/seg_msh.h>

namespace hl7parsercpp {
  class HL7Header : public HL7Base {
  public:
    HL7Header(HL7_Message* message_) : HL7Base(message_, "MSH", 0) {}

    string FieldSeparator() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 0);
      });
    }
    string EncodingCharacters() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 1);
      });
    }
    vector<string> SendingApplication() {
      auto results = getComponents(2);
      return move(results);
    }
    vector<string> SendingFacility() {
      auto results = getComponents(3);
      return move(results);
    }
    vector<string> ReceivingApplication() {
      auto results = getComponents(4);
      return move(results);
    }
    vector<string> ReceivingFacility() {
      auto results = getComponents(5);
      return move(results);
    }
    string DateTimeOfMessage() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 6);
      });
    }
    string Security() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 7);
      });
    }
    vector<string> MessageType() {
      auto results = getComponents(8);
      return move(results);
    }
    string MessageControlID() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 9);
      });
    }
    vector<string> ProcessingID() {
      auto results = getComponents(10);
      return move(results);
    }
    vector<string> VersionID() {
      auto results = getComponents(11);
      return move(results);
    }
    string SequenceNumber() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 12);
      });
    }
    string ContinuationPointer() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 13);
      });
    }
    string AcceptAcknowledgmentType() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 14);
      });
    }
    string ApplicationAcknowledgmentType() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 15);
      });
    }
    string CountryCode() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 16);
      });
    }
    string CharacterSet() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 17);
      });
    }
    vector<string> PrincipalLanguageOfMessage() {
      auto results = getComponents(18);
      return move(results);
    }
    string AlternateCharacterSetHandlingScheme() {
      return getString([](HL7_Segment* seg) {
        return hl7_segment_field(seg, 19);
      });
    }
    vector<string> MessageProfileIdentifier() {
      auto results = getComponents(20);
      return move(results);
    }

    vector<pair<string, string>> Header() {
      return {
        { "FieldSeparator", FieldSeparator() },
        { "EncodingCharacters", EncodingCharacters() },
        { "SendingApplication", concat(SendingApplication(), "^") },
        { "SendingFacility", concat(SendingFacility(), "^") },
        { "ReceivingApplication", concat(ReceivingApplication(), "^") },
        { "ReceivingFacility", concat(ReceivingFacility(), "^") },
        { "DateTimeOfMessage", DateTimeOfMessage() },
        { "Security", Security() },
        { "MessageType", concat(MessageType(), "^") },
        { "MessageControlID", MessageControlID() },
        { "ProcessingID", concat(ProcessingID(), "^") },
        { "VersionID", concat(VersionID(), "^") },
        { "SequenceNumber", SequenceNumber() },
        { "ContinuationPointer", ContinuationPointer() },
        { "AcceptAcknowledgmentType", AcceptAcknowledgmentType() },
        { "ApplicationAcknowledgmentType", ApplicationAcknowledgmentType() },
        { "CountryCode", CountryCode() },
        { "CharacterSet", CharacterSet() },
        { "PrincipalLanguageOfMessage", concat(PrincipalLanguageOfMessage(), "^") },
        { "AlternateCharacterSetHandlingScheme", AlternateCharacterSetHandlingScheme() },
        { "MessageProfileIdentifier", concat(MessageProfileIdentifier(), "^") }
      };
    };

    string sendingApplicationId() {
      return getString(hl7_msh_sending_application_id);
    }
    string sendingFacilityId() {
      return getString(hl7_msh_sending_facility_id);
    }
    string sendingFacilityUniversalId() {
      return getString(hl7_msh_sending_facility_universal_id);
    }
    string sendingFacilityUniversalIdType() {
      return getString(hl7_msh_sending_facility_universal_id_type);
    }
  };
}
