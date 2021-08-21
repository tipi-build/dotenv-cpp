#include <iostream>
#include <dotenv/dotenv.hpp>

int main(int argc, char **argv) {
  
  dotenv::use_dotenv_file("/Users/luclambour/workspace/dotenv-cpp/test/.env");
  std::cout<<std::getenv("PORT")<<std::endl;
  std::cout<<std::getenv("COUPLE")<<std::endl;
  std::cout<<std::getenv("BASE_URL")<<std::endl;
  std::cout<<std::getenv("KEYSSH")<<std::endl;

  dotenv::getenv_or_value("CRIM1","Calamity Jane");
  //Must be Bonnie 
  std::cout<<std::getenv("CRIM1")<<std::endl;
  dotenv::getenv_or_value("CRIM3","Calamity Jane");
  std::cout<<std::getenv("CRIM3")<<std::endl;





  return 0;
}