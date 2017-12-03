#ifndef HL7PARSER_DLL
#define HL7PARSER_DLL
#endif

#include "hl7parser-json.hpp"
#include <regex>
#include <map>
#include <functional>

#include <hl7parser/seg_pid.h>
#include <hl7parser/seg_obx.h>

using namespace hl7parserJson;
using namespace std;

static char MESSAGE_DATA[] =
"MSH|^~\\&|SERV|223344^^II|POSM|CARRIER^CL9999^IP|20030127202538||RPA^I08|5307938|P|2.3|||NE|NE\r"
"MSA|AA|CL999920030127203647||||B006^\r"
"AUT|TESTPLAN|223344^^II||||5307938||0|0\r"
"PRD|RT|NOMBRE PRESTADOR SALUD|||||99999999999^CU^GUARDIA\r"
"PRD|RP||||||9^^N\r"
"PID|||2233441000013527101=0000000000002|1|NOMBRE PACIENTE^\r"
"PR1|1||420101^CONSULTA EN CONSULTORIO^NA^||20030127203642|Z\r"
"AUT|PLANSALUD|||20030127|20030127|5307938|0.00^$|1|1\r"
"NTE|1||SIN CARGO\r"
"NTE|2||IVA: SI\r";

string getSampleFile(const string& filename = "data/adt_a08.txt") {
  regex newline("\n");
  ifstream infile{ filename };
  if (infile.fail()) {
    cerr << strerror(errno) << endl;
    return "";
  }
  string file_contents{ istreambuf_iterator<char>(infile), istreambuf_iterator<char>() };
  return regex_replace(file_contents, newline, "\r");
}

void testParse(string input) {
  hl7parser<Format::json> parser;
  try {
    string result = parser.parse(input);
    cout << result << endl;;
  } catch (exception& e) {
    cout << e.what() << endl;
  }
}

int testFile() {
  auto a08 = getSampleFile();
  testParse(a08);
  return 0;
}

void testHeaderOnly(string input) {
  hl7parser<Format::json> parser;
  try {
    string result = parser.parseHeader(input);
    cout << result << endl;;
  } catch (exception& e) {
    cout << e.what() << endl;
  }
}

typedef HL7_Element* GetHL7ElementFunc(HL7_Segment*);

class HL7Base {
public:
  HL7Base(HL7_Message* message_) : message(message_) {}
  HL7Base(HL7_Segment* segment_) : segment(*segment_) {}
protected:
  HL7_Segment segment;
  HL7_Message* message;

  string getString(GetHL7ElementFunc f) {
    HL7_Element* el;
    el = f(&segment);
    string m(el->value, el->length);
    return move(m);
  }
};

class HL7Patient : public HL7Base {
public:
  HL7Patient(HL7_Message* message_) : HL7Base(message_) {
    hl7_message_segment(message, &segment, "PID", 0);
  }
  string patientId() {
    return getString(hl7_pid_patient_id);
  }
  string firstName() {
    return getString(hl7_pid_first_name);
  }
  string lastName() {
    return getString(hl7_pid_last_name);
  }
};

class HL7Observation : public HL7Base {
public:
  HL7Observation(HL7_Message* message_) : HL7Base(message_) {}

  HL7Observation(HL7_Segment* segment_) : HL7Base(segment_) {}

  vector<string> observationValues() {
    vector<string> vals;
    int row_idx = 0;
    int rc = 0;
    string m;

    while (rc == 0) {
      rc = hl7_message_segment(message, &segment, "OBX", row_idx);
      if (rc == 0) {
        // el = hl7_obx_observation_value_text(&segment);
        // Same as: el = hl7_segment_field(&segment, 4);
        m = getString(hl7_obx_observation_value_text);
        if (m.size() == 0) {
          // el = hl7_obx_observation_value(&segment);
          // Same as: el = hl7_segment_component(&segment, 4, 0);
          // Ideally, should iterate all subcomponents (ie, (4, 0), (4, 1), ...), if known.
          m = getString(hl7_obx_observation_value);
        }
        vals.push_back(move(m));        
      }
      ++row_idx;
    }
    return vals;
  }
};

class HL7Message {
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
    /* Cleanup */
    hl7_buffer_fini(&output_buffer);
    
    hl7_parser_fini(&parser);

    hl7_message_fini(&message);
    hl7_allocator_fini(&allocator);

    hl7_buffer_fini(&input_buffer);
    hl7_settings_fini(&settings);
  }

  void parse(const string& hl7string_ = "") {
    if (hl7string_.size() > 0)
      hl7string = hl7string_;

    if (hl7string.size() == 0) return;

    message_length = hl7string.size();
    hl7_settings_init(&settings);

    /* Initialize the buffer excluding the null terminator. */
    hl7_buffer_init(&input_buffer, const_cast<char*>(hl7string.c_str()), message_length);
    hl7_buffer_move_wr_ptr(&input_buffer, message_length);

    /* Initialize the message */
    hl7_allocator_init(&allocator, malloc, free);
    hl7_message_init(&message, &settings, &allocator);

    /* Initialize the parser. */
    hl7_parser_init(&parser, &settings);

    rc = hl7_parser_read(&parser, &message, &input_buffer);
  }

  shared_ptr<HL7Patient> patient() {
    return make_shared<HL7Patient>(&message);
  }

  vector<shared_ptr<HL7Observation>> observations() {
    size_t row_idx = 0;
    int rc = 0;
    while (rc == 0) {
      rc = hl7_message_segment(&message, &segment, "OBX", row_idx);

      if (rc == 0) {
        auto observation = HL7Observation{&segment};
      }

      ++row_idx;
    }
  }
};

void processMessage(HL7_Message* message) {
  int rc = 0, row_idx = 0;
  HL7_Segment segment;
  HL7_Element* el;
  regex ex("y", regex_constants::icase | regex_constants::ECMAScript);
  
  // Patient
  HL7Patient patient{message};
  cout << patient.patientId() << endl;
  cout << patient.firstName() << endl;
  cout << patient.lastName() << endl;

  HL7Observation observation{message};

  auto vals = observation.observationValues();
  for(const auto& e : vals) {
    cout << e << endl;
  }

  // Find "Y" in list of observations.
  auto it = find_if(vals.begin(), vals.end(), [&ex](const auto& m)->bool { return std::regex_match(m, ex); });

  if (it != vals.end()) {
    cout << *it << endl;
  }

}

int testLibParse() {
  int             rc = 0;
  HL7_Settings    settings;
  HL7_Buffer      input_buffer;
  HL7_Buffer      output_buffer;
  HL7_Allocator   allocator;
  HL7_Message     message;
  HL7_Parser      parser;
  size_t          message_length = sizeof(MESSAGE_DATA) - 1;

  auto mdm = getSampleFile("internal/realmdm.txt");
  message_length = mdm.size();

  {
    HL7Message hl7m{"fail"};
  }
  {
    HL7Message hl7m{""};
  }
  {
    HL7Message hl7m{mdm};
    auto patient = hl7m.patient();
    cout << patient->firstName() << endl;

    auto observations = hl7m.observations();
  }

  hl7_settings_init(&settings);

  /* Initialize the buffer excluding the null terminator. */
  hl7_buffer_init(&input_buffer, const_cast<char*>(mdm.c_str()), message_length);
  hl7_buffer_move_wr_ptr(&input_buffer, message_length);

  /* Initialize the message */
  hl7_allocator_init(&allocator, malloc, free);
  hl7_message_init(&message, &settings, &allocator);

  /* Initialize the parser. */
  hl7_parser_init(&parser, &settings);

  rc = hl7_parser_read(&parser, &message, &input_buffer);
  
  if (rc == 0) {
    processMessage(&message);
  }

  /* Cleanup */
  hl7_buffer_fini(&output_buffer);
  
  hl7_parser_fini(&parser);

  hl7_message_fini(&message);
  hl7_allocator_fini(&allocator);

  hl7_buffer_fini(&input_buffer);
  hl7_settings_fini(&settings);

  return rc;
}

int main(int argc, char *argv[]) {
  return testLibParse();
  testHeaderOnly(MESSAGE_DATA);
  testFile();
  testParse(MESSAGE_DATA);  
}