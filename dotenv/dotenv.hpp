#pragma once
#include <iostream>
#include <vector>
#include <optional>
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <dotenv/detail/common/common.hpp>
#include <dotenv/detail/usefile/usefile.hpp>
#include <dotenv/detail/formap/formap.hpp>



namespace dotenv {


struct dotenv {

  dotenv(std::map<std::string,std::string>maps_for_env = {} ,std::string path_filename=".env", bool preserve = true){
    path_filename_ = path_filename;
    preserve_ = preserve;
    maps_for_env_ = maps_for_env;
  }

    dotenv(std::string path_filename=".env", bool preserve = true){
    path_filename_ = path_filename;
    preserve_ = preserve;
    maps_for_env_ = {};
  }

  inline void getenv_or_value(std::string environment_name, std::string default_value) {
    if (!(std::getenv(environment_name.c_str()))) {
      dotenv::detail::common::set_environment(environment_name.c_str(), default_value.c_str());
    }
  }

  inline void use_dotenv_file(){
    std::map<std::string, std::string> maps_from_dotenv = dotenv::detail::usefile::read_file_dotenv(path_filename_);
    std::map<std::string, std::string> tempory_maps_env_ = maps_for_env_;
    for (const auto &[key, value] : maps_from_dotenv) {
      auto key_search = tempory_maps_env_.find(key);
      if (key_search != tempory_maps_env_.end()) {
        tempory_maps_env_.erase(key);
      }
    }

    for (const auto &[key, value] : maps_from_dotenv) {
      std::pair<std::string, std::string> pair_for_insert{key,value};
      tempory_maps_env_.insert(pair_for_insert);   
    }

    bool map_contains_ref = true;

    while (map_contains_ref){
      dotenv::detail::formap::transform_in_final_map(tempory_maps_env_);
      map_contains_ref= dotenv::detail::formap::is_map_contains_ref(tempory_maps_env_);
    }

    if (preserve_){
      maps_env_ = dotenv::detail::formap::set_environment_with_preserve_for_map(tempory_maps_env_);
    }else {
      maps_env_ = dotenv::detail::formap::set_environment_without_preserve_for_map(tempory_maps_env_);
    }
  }

  inline std::map<std::string, std::string> get_maps_env(){
    return maps_env_;
  }

  inline void print_map_env(){
    std::cout << "Your environmental values are : " << std::endl;
    for (auto map : maps_env_) {
      std::cout << "- Key : " << map.first << "\n- Value : " << map.second << std::endl;
    }
  }

public :
std::string path_filename_;
std::map<std::string, std::string> maps_for_env_{};
bool preserve_;

private :
std::map<std::string, std::string> maps_env_{};

};  
}