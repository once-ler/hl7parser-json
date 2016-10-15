#include "hl7parser-json.hpp"

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

int main(int argc, char *argv[]) {
  hl7parser<Format::json> parser;
  try {
    string result = parser.parse(MESSAGE_DATA);
    cout << result << endl;;
  } catch (exception& e) {
    cout << e.what() << endl;
  }
}