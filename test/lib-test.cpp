#include <iostream>
#include <dotenv/dotenv.hpp>

int main(int argc, char **argv) {
  
  std::map<std::string, std::string> far_west{{"CRIM1", "Calamity Jane"},{"CRIM3", "Calamity Jane"}
                                             ,{"CRIM4", "Bob Dalton"}, {"CRIM5", "Emmett Dalton"}
                                             ,{"CRIM6", "William Dalton"},{"CRIM7", "Gratton Dalton"}
                                             ,{"CRIMINAL_FAMILY", "${CRIM4} & ${CRIM5} & ${CRIM6} & ${CRIM7}"}};
  
  dotenv::dotenv Env_app(far_west,"/Users/luclambour/workspace/tipi-build/dotenv-cpp/test/.env",true);
  Env_app.use_dotenv_file();
  Env_app.print_map_env();
  return 0;
}