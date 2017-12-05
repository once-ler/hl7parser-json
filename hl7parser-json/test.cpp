#ifndef HL7PARSER_DLL
#define HL7PARSER_DLL
#endif

#include "hl7parser-json.hpp"
#include "HL7Message.hpp"
#include <regex>
#include <map>
#include <functional>

#include <hl7parser/seg_pid.h>
#include <hl7parser/seg_obx.h>

using namespace hl7parserJson;
using namespace hl7parsercpp;
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

int main(int argc, char *argv[]) {
  return testLibParse();
  testHeaderOnly(MESSAGE_DATA);
  testFile();
  testParse(MESSAGE_DATA);  
}