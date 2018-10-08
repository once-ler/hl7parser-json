#ifndef HL7PARSER_DLL
#define HL7PARSER_DLL
#endif

#include "hl7parser-json.hpp"
#include "HL7Message.hpp"
#include "HL7Util.hpp"
#include "model/hl7MessageModel.hpp"
#include <regex>
#include <map>
#include <functional>
#include <fstream>

#include <hl7parser/seg_pid.h>
#include <hl7parser/seg_obx.h>

using namespace hl7parserJson;
using namespace hl7parsercpp;
using namespace hl7parsercpp::util;
using namespace hl7parserrxweb::model;
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
  regex newline("\r\n");
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
  
  // auto mdm = getSampleFile("internal/realmdm.txt");
  auto mdm = getSampleFile("internal/adt_a31.txt");

  {
    HL7Message hl7m{"fail"};
  }
  {
    HL7Message hl7m{""};
  }
  {
    HL7Message hl7m{mdm};
    auto header = hl7m.header();

    auto hm = header->Header();

    auto msg_type = hl7m.toComponentString(header->MessageType());
    auto msg_ctrl_id = header->MessageControlID();

    auto ackMessage = hl7m.acknowledgment();

    auto patient = hl7m.patient();
    auto pa = patient->Patient();
    auto pid_id = patient->patientId();

    auto patient_j = patient->toJson();
    patient_j["_id"] = pid_id;
    patient_j["mrn"] = pid_id;
    cout << patient_j.dump(2) << endl;

    string streamType = strings::concat(msg_type, string(":"), pid_id);

    cout << hl7m.streamType() << endl;

    HL7MessageModel hl7_j{ mdm };
    json j_ = hl7_j;
    cout << j_.dump(2) << endl;

    // cout << ackMessage << endl;
    ofstream f("internal/test.ack");
    f << ackMessage;
    f.close();
  }  
  {
    HL7Message hl7m{mdm};
    auto patient = hl7m.patient();
    cout << patient->firstName() << endl;

    auto x = patient->PatientIdentifierListX();

    cout << hl7m.toComponentString(patient->PatientIdentifierList()) << endl;
    cout << patient->DateTimeOfBirth() << endl;
    cout << patient->AdministrativeSex() << endl;
    cout << hl7m.toComponentString(patient->Race()) << endl;
    cout << hl7m.toComponentString(patient->PatientAddress()) << endl;
    cout << hl7m.toComponentString(patient->PhoneNumberHome()) << endl;
    cout << hl7m.toComponentString(patient->EthnicGroup()) << endl;

    auto observations = hl7m.observations();

    for(const auto o : observations) {
      auto vals = o->ObservationValues();     
      auto obs = hl7m.toComponentString(vals);

      cout << obs << endl;

      // Find "Y" in list of observations.
      regex ex("y", regex_constants::icase | regex_constants::ECMAScript);
      auto it = find_if(vals.begin(), vals.end(), [&ex](const auto& m)->bool { return std::regex_match(m, ex); });

      if (it != vals.end()) {
        cout << *it << endl;
      }
    }

  }
}

int testRepeatableFields() {
  const string hl7msg =
      "MSH|^~\\&|SENDING_APPLICATION|SENDING_FACILITY|RECEIVING_APPLICATION|RECEIVING_FACILITY|20110613072049||ADT^A08|934579920110613072049|P|2.3||||\r"
      "PID|1||135769||MOUSE^MICKEY^||19281118|M||W|123 Main St.^^Lake Buena Vista^FL^32830||(407)939-1289^^^theMainMouse@disney.com|||||1719|99999999|||N~U|||||||||||||||||\r";

      // "PID|1||135769||MOUSE^MICKEY^||19281118|M||W~B~I|123 Main St.^^Lake Buena Vista^FL^32830||(407)939-1289^^^theMainMouse@disney.com|||||1719|99999999|||N~U|||||||||||||||||\r";

  HL7Message hl7m{hl7msg};

  HL7_Message* message = hl7m.getMessage();

  // Component 4 -> Name, 9 -> Race
  vector<string> vals;
  HL7_Element* el;
  HL7_Segment segment;
  string m;
  int idx = 0, pos = 9;
  
  hl7_message_segment(message, &segment, "PID", 0);

  do {
    el = hl7_segment_component(&segment, pos, idx);
    if ((!(el->length ^ el->attr)) == 1) {
      el = hl7_segment_repetition(&segment, pos, idx);
      
      if ((!(el->length ^ el->attr)) == 1)
        break;
    }

    m = el->length > 0 ? string(el->value, el->length) : "";
    
    vals.push_back(move(m));

    ++idx;
  } while (true);

  return 0;
}

int main(int argc, char *argv[]) {
  return testRepeatableFields();
  return testLibParse();
  testHeaderOnly(MESSAGE_DATA);
  testFile();
  testParse(MESSAGE_DATA);  
}