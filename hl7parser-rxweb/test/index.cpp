#include "test.hpp"
#include "json.hpp"

using json = nlohmann::json;

namespace hl7parserrxweb::test::fixtures {
  json config_j = {
    {
      "hl7", {
        { "port", 1717 },
        { "threads", 20 }
      }
    },
    {
      "universalConsent", {
        { "processState", "Foo" },
        { "store", "Epic" },
        { "studyId", "foobar123" }
      }
    },
    { "mongo", {
        { "development", {
            { "uri", "" },
            { "database", "" }
          }
        },
        { "staging", {
            { "uri", "mongodb://127.0.0.1:27017" },
            { "database", "test" }
          }
        },
        { "prod", {
            { "uri", "" },
            { "database", "" }
          }
        }
      }
    },
    { "mssql", {
        { "development", {
            { "server", "" },
            { "port", 1433  },
            { "database", "" },
            { "user", "" },
            { "password", "" }
          }
        },
        { "staging", {
            { "server", "" },
            { "port", 1433  },
            { "database", "" },
            { "user", "" },
            { "password", "" }
          }
        },
        { "prod", {
            { "server", "" },
            { "port", 1433  },
            { "database", "" },
            { "user", "" },
            { "password", "" }
          }
        }
      }
    }
  };

}

int main(int argc, char *argv[]) {
  using namespace hl7parserrxweb::test;

  hl7parserrxweb::test::start("staging", fixtures::config_j);

}
