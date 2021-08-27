#include <iostream>
#include <dotenv/dotenv.hpp>

int main(int argc, char **argv) {

  dotenv::use_dotenv_file("/Users/luclambour/workspace/dotenv-cpp/test/.env");
   std::map<std::string, std::string> far_west{{"CRIM1", "Calamity Jane"},  {"CRIM4", "Bob Dalton"},
                                              {"CRIM5", "Emmett Dalton"},  {"CRIM6", "William Dalton"},
                                              {"CRIM7", "Gratton Dalton"}, {"CRIMINAL_FAMILY", "${CRIM4} & ${CRIM5} & ${CRIM6} & ${CRIM7}"}};
  dotenv::use_dotenv_map(far_west);

  dotenv::getenv_or_value("CRIM1", "Calamity Jane");
  // Must be Bonnie
  std::cout << std::getenv("CRIM1") << std::endl;
  dotenv::getenv_or_value("CRIM3", "Calamity Jane");
  std::cout << std::getenv("CRIM3") << std::endl;

 




  return 0;
}