#include <iostream>
#include <dotenv.hpp>

int main(int argc, char **argv) {
  
  dotenv::use_dotenv_file("/Users/luclambour/Desktop/Workspace/dotenv-cpp/test/.env");
  std::cout<<std::getenv("PORT")<<std::endl;
  std::cout<<std::getenv("COUPLE")<<std::endl;
  std::cout<<std::getenv("BASE_URL")<<std::endl;
  std::cout<<std::getenv("KEYSSH")<<std::endl;

  return 0;
}