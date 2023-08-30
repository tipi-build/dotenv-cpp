#pragma once
 #include <iostream>
 #include <vector>
 #include <map>
 #include <fstream>
 #include <string>
 #include <stdlib.h>
 #include <utility>

 namespace dotenv::detail::common {

  inline void set_environment(std::string key, std::string value) {
 #ifdef _WIN32
     _putenv_s(key.c_str(), value.c_str());
 #else
     setenv(key.c_str(), value.c_str(), 1);
 #endif
   }

  inline void print_map(const std::map<std::string, std::string> &map_to_print) {
     for (const auto &[key, value] : map_to_print) {
      std::cout << key << "  " << value << std::endl;
     }
   }

  inline std::string get(std::string environment_name){
    std::string value="";
    if (std::getenv(environment_name.c_str()) != nullptr){
      value =std::getenv(environment_name.c_str());
    }
    return value;
  }

  inline bool is_string_contains_ref(std::string value) {
     bool contains_ref = false;
     std::string search = "${";
     std::size_t found = value.find(search);
     if (found != std::string::npos) {
       contains_ref = true;
     }
     return contains_ref;
   }

}