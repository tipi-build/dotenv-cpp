#include <iostream>
#include <dotenv/dotenv.hpp>

int main(int argc, char **argv) {

   std::map<std::string, std::string> far_west{{"CRIM1", "Calamity Jane"},  {"CRIM4", "Bob Dalton"},
                                              {"CRIM5", "Emmett Dalton"},  {"CRIM6", "William Dalton"},
                                              {"CRIM7", "Gratton Dalton"}, {"CRIMINAL_FAMILY", "${CRIM4} & ${CRIM5} & ${CRIM6} & ${CRIM7}"}};

  dotenv::use_dotenv_file_map("/Users/luclambour/workspace/dotenv-cpp/test/.env",far_west,true);
  return 0;
}