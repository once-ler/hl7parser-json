#pragma once

#include "json.hpp"
#include "hl7parser-json/include/hl7parser-json.hpp"

using namespace std;
using json = nlohmann::json;

namespace hl7parserJson {

  class JsonHL7Parser {

  public:

    json parse(const string& hl7string) {
      if (hl7string.size() == 0 || !hl7AsJson.is_null())
        return hl7AsJson;

      json j;
      
      try {
        auto jstr = hl7ParserJson.parse(hl7string);
        j = json::parse(jstr);

        string p = "/Message/Segment";
        
        auto jp = json::json_pointer(p);

        try {
          auto j2 = j.value("/Message/Segment"_json_pointer, json::array({}));

          for (auto& f : j2) {
            auto v = f.at("Field");
              if (!v.is_array())
                continue;
              string k = v.at(0).get<std::string>();
              v.erase(0);
              hl7AsJson[k] = v;
          }
        } catch (const exception& e) {
          cout << e.what() << endl;
        }

      } catch (json::parse_error& e) {
        std::cout << "message: " << e.what() << '\n'
          << "exception id: " << e.id << '\n'
          << "byte position of error: " << e.byte << std::endl;
      } catch (exception& e) {
        cout << e.what() << endl;
      }
      return hl7AsJson;
    }

  private:
    json hl7AsJson;  
    hl7parser<Format::json> hl7ParserJson;
  };

}

