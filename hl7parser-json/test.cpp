#include "hl7parser-json.hpp"
#include <regex>

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
    HL7_Segment segment;
    HL7_Element* el;
    int sequence = 0;
    
    rc = hl7_message_segment(&message, &segment, "PID", 0);
    if (rc == 0) {
      // Patient
      el = hl7_pid_patient_id(&segment);
      string m(el->value, el->length);
      cout << m << endl;
    }

    rc = hl7_message_segment(&message, &segment, "OBX", 1);
    if (rc == 0) {
      // Observation
      el = hl7_obx_observation_value_text(&segment);
      cout << el->length << endl;
      el = hl7_obx_observation_value(&segment);
      auto tk = el->attr;
      string m(el->value, el->length);
      cout << m << endl;
    }
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