#pragma once

#include "HL7Header.hpp"
#include "HL7Patient.hpp"
#include "HL7Observation.hpp"
#include "HL7Util.hpp"

using namespace hl7parsercpp::util;

namespace hl7parsercpp {
  static string version = "0.3.4";

  class HL7Message {
    friend HL7Header;
    friend HL7Patient;
    friend HL7Observation;

    string hl7string;
    int             rc = -1;
    HL7_Settings    settings;
    HL7_Buffer      input_buffer;
    HL7_Buffer      output_buffer;
    HL7_Allocator   allocator;
    HL7_Message     message;
    HL7_Segment segment;
    HL7_Parser      parser;
    size_t          message_length = 0;
  public:
    HL7Message() = default;
    HL7Message(const string& hl7string_) : hl7string(hl7string_) {
      parse();
    }
    ~HL7Message() {
      if (rc != 0) return;
      // Cleanup
      hl7_buffer_fini(&output_buffer);
      
      hl7_parser_fini(&parser);

      hl7_message_fini(&message);
      hl7_allocator_fini(&allocator);

      hl7_buffer_fini(&input_buffer);
      hl7_settings_fini(&settings);
    }

    string toComponentString(const vector<string> vals) {
      stringstream all;
      copy(vals.begin(), vals.end(), ostream_iterator<string>(all, "^"));
      string s = all.str();
      s.pop_back();
      return move(s);
    }

    void parse(const string& hl7string_ = "") {
      if (hl7string_.size() > 0)
        hl7string = hl7string_;

      if (hl7string.size() == 0) return;

      message_length = hl7string.size();
      hl7_settings_init(&settings);

      // Initialize the buffer excluding the null terminator.
      hl7_buffer_init(&input_buffer, const_cast<char*>(hl7string.c_str()), message_length);
      hl7_buffer_move_wr_ptr(&input_buffer, message_length);

      // Initialize the message.
      hl7_allocator_init(&allocator, malloc, free);
      hl7_message_init(&message, &settings, &allocator);

      // Initialize the parser.
      hl7_parser_init(&parser, &settings);

      rc = hl7_parser_read(&parser, &message, &input_buffer);
    }

    shared_ptr<HL7Header> header() {
      return make_shared<HL7Header>(&message);
    }

    shared_ptr<HL7Patient> patient() {
      return make_shared<HL7Patient>(&message);
    }

    vector<shared_ptr<HL7Observation>> observations() {
      vector<shared_ptr<HL7Observation>> obs;
      size_t row_idx = 0;
      int rc = 0;
      while (rc == 0) {
        rc = hl7_message_segment(&message, &segment, "OBX", row_idx);

        if (rc == 0) {
          auto observation = make_shared<HL7Observation>(&message, row_idx);
          obs.push_back(move(observation));
        }

        ++row_idx;
      }
      return obs;
    }

    string acknowledgment() {
      auto header = this->header();
      auto hm = header->Header();

      auto ackSuccess = hof::map<pair<string,string>, string>(hm, [](const auto& e) {
        if (e.first == "FieldSeparator") return string("");
        if (e.first == "MessageType") return strings::concat(string("ACK^"), strings::split(e.second, '^')[1]);
        return e.second;
      });

      auto ackMessage = strings::concat(
        string("MSH|"),
        strings::join(ackSuccess.begin(), ackSuccess.end(), string("|")),
        string("\rMSA|AA|"),
        header->MessageControlID(),
        string("||||")
      );

      return move(ackMessage);
    }

  };
}
