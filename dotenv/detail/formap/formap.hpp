#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <dotenv/detail/common/common.hpp>

namespace dotenv::detail::formap {

  inline bool is_map_contains_ref(std::map<std::string, std::string> checks_maps) {
    bool contains_ref = false;
    std::string search = "${";
    for (auto check : checks_maps) {
      std::string value = check.second;
      std::size_t found = value.find(search);
      if (found != std::string::npos) {
        contains_ref = true;
      }
    }
    return contains_ref;
  }

  inline std::string found_value_of_reference_map(std::map<std::string, std::string> &maps_for_env, std::string &ref) {
    std::string value_to_return{};
    std::string search_dollar_begin_bracket = "${";
    int size_search_d = search_dollar_begin_bracket.size();
    std::string search_end_bracket = "}";

    for (auto map_for_env : maps_for_env) {
      if (map_for_env.first == ref) {
        std::size_t found_begin = map_for_env.second.find(search_dollar_begin_bracket);
        std::size_t found_end = map_for_env.second.find(search_end_bracket);
        int legnth_to_save = found_end - (found_begin + size_search_d);
        std::string ref_name_in_map{};
        if (found_begin != std::string::npos){
          ref_name_in_map = map_for_env.second.substr(found_begin + size_search_d, legnth_to_save);
        }
        if (ref_name_in_map != ref){
           value_to_return = map_for_env.second;
        }       
        break;
      }
    }

    if (value_to_return.empty()) {
      value_to_return = dotenv::detail::common::get(ref);
      if (value_to_return.empty()) {
        std::cout << "To use a reference in the values of the map  you have to write correctly (warning it is case "
                    "sensitive) the name and make that it exists"
                  << std::endl;
        std::exit(1);
      }
    }
    return value_to_return;
  }

  inline void transform_in_final_map(std::map<std::string, std::string> &maps_of_future_env) {
    std::string search_dollar_begin_bracket = "${";
    int size_search_d = search_dollar_begin_bracket.size();
    std::string search_end_bracket = "}";

    for (auto &map : maps_of_future_env) {
      bool contains_ref = dotenv::detail::common::is_string_contains_ref(map.second);
      if (contains_ref) {
        std::string ref_name;
        std::size_t found_begin = map.second.find(search_dollar_begin_bracket);
        std::size_t found_end = map.second.find(search_end_bracket);
        if (found_begin != std::string::npos) {
          std::string transformed_value = map.second;
          int legnth_to_save = found_end - (found_begin + size_search_d);
          ref_name = map.second.substr(found_begin + size_search_d, legnth_to_save);
          int only_ref_complete = (search_dollar_begin_bracket + ref_name + search_end_bracket).size();
          std::string ref_value = dotenv::detail::formap::found_value_of_reference_map(maps_of_future_env, ref_name);
          transformed_value.replace(found_begin, only_ref_complete, ref_value);
          map.second = transformed_value;
        }
      }
    }
  }

  inline std::map<std::string, std::string> set_environment_with_preserve_for_map(std::map<std::string, std::string> future_env) {
    std::map<std::string, std::string> map_set_in_environment;
    for (auto map : future_env) {
      std::string key = map.first;
      std::string value;
      if (!(std::getenv(map.first.c_str()))) {
        value = map.second;
        dotenv::detail::common::set_environment(map.first.c_str(), map.second.c_str());
      }else {
        value = std::getenv(map.first.c_str());
      }
      std::pair<std::string, std::string> pair_for_insert {key,value};
      map_set_in_environment.insert(pair_for_insert);
    }
    return map_set_in_environment;
  }

  inline std::map<std::string, std::string> set_environment_without_preserve_for_map(std::map<std::string, std::string> future_env) {
    std::map<std::string, std::string> map_set_in_environment;
    for (auto map : future_env) {
      std::string key = map.first;
      std::string value=map.second;
      std::pair<std::string, std::string> pair_for_insert {key,value};
      map_set_in_environment.insert(pair_for_insert);
      dotenv::detail::common::set_environment(map.first.c_str(), map.second.c_str());
    }
    return map_set_in_environment;
  }
}