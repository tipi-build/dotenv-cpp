#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <utility>
#include <dotenv/pre/common/common.hpp>

namespace dotenv::pre::usefile {
    
  inline std::map<std::string, std::string> parse_file_string(std::string line) {
    std::string search_equal = "=";
    std::size_t found = line.find(search_equal);
    std::string key = "";
    std::string value = "";
    int size_line = line.size();

    if (found != std::string::npos) {
      key = line.substr(0, found);
      value = line.substr(found + 1, size_line);
    }

    std::map<std::string, std::string> string_parse{{key, value}};
    return string_parse;
  }

  inline bool is_multine(std::string line, std::string &key_multiline, bool multiline) {
    if (!(multiline)) {
      std::string search_equal_quote = R"(=")";
      std::size_t found = line.find(search_equal_quote);
      if (found != std::string::npos) {
        multiline = true;
        key_multiline = line.substr(0, found);
      }
    }
    return multiline;
  }

  inline bool is_end_of_multiline(std::string line) {
    bool multiline = false;
    int line_size = line.size();
    if (line[line_size - 1] == '"') {
      multiline = true;
    }
    return multiline;
  }

  inline std::string value_begin_multiline(std::string line) {
    std::string search_equal_quote = R"(=")";
    std::size_t found = line.find(search_equal_quote);
    int size_line = line.size();
    std::string value = line.substr(found + 2, size_line);
    value = value + "\n";
    return value;
  }

  inline std::string value_end_multline(std::string line) {
    int size_line = line.size();
    line.resize(size_line - 1);
    return line;
  }

  inline std::vector<std::map<std::string, std::string>> read_file_dotenv(std::string path_filename) {
    std::vector<std::map<std::string, std::string>> vector_of_future_env;
    std::fstream file(path_filename.c_str(), file.binary | file.in | file.out);

    std::string line;
    std::string key_multi = "";
    bool multiline = false;
    bool end_of_multiline = false;
    std::string value_multiline = "";
    while (std::getline(file, line)) {
      if (!(line[0] == '#')) {
        multiline = dotenv::pre::usefile::is_multine(line, key_multi, multiline);
        end_of_multiline = dotenv::pre::usefile::is_end_of_multiline(line);

        if ((multiline) && (!(end_of_multiline))) {
          if (dotenv::pre::usefile::is_multine(line, key_multi, false)) {
            value_multiline = dotenv::pre::usefile::value_begin_multiline(line);
          } else {
            value_multiline = value_multiline + line + "\n";
          }
        } else if (multiline && end_of_multiline) {
          value_multiline = value_multiline + dotenv::pre::usefile::value_end_multline(line);
          std::map<std::string, std::string> map_for_insert{{key_multi, value_multiline}};
          vector_of_future_env.push_back(map_for_insert);
          key_multi = "";
          value_multiline = "";
          multiline = false;
        } else {
          vector_of_future_env.push_back(dotenv::pre::usefile::parse_file_string(line));
        }
      }
    }
    return vector_of_future_env;
  }

  inline bool is_vector_contains_ref(std::vector<std::map<std::string, std::string>> vector_of_future_env) {
    bool contains_ref = false;
    std::string search = "${";

    for (auto vector : vector_of_future_env) {
      for (const auto &[key, value] : vector) {
        std::size_t found = value.find(search);
        if (found != std::string::npos) {
          contains_ref = true;
        }
      }
    }
    return contains_ref;
  }
  inline std::string found_value_of_reference(std::vector<std::map<std::string, std::string>> &vector_of_future_env,
                                              std::string ref) {
    std::string value_to_return;
    for (auto vector : vector_of_future_env) {
      for (const auto &[key, value] : vector) {
        if (ref == key) {
          value_to_return = value;
        }
      }
    }
    if (value_to_return.empty()) {
      std::cout << "To use a reference in the values of the .env file you have to write correctly (warning it is case "
                   "sensitive) the name and make that it exists"
                << std::endl;
      std::exit(1);
    }
    return value_to_return;
  }
  inline void transform_in_final_vector(std::vector<std::map<std::string, std::string>> &vector_of_future_env) {
    int vector_size = vector_of_future_env.size();
    std::string search_dollar_begin_bracket = "${";
    int size_search_d = search_dollar_begin_bracket.size();
    std::string search_end_bracket = "}";
    std::string ref_name;

    for (int index = 0; index < vector_size; ++index) {

      for (const auto &[key, value] : vector_of_future_env[index]) {
        std::size_t found_begin = value.find(search_dollar_begin_bracket);
        std::size_t found_end = value.find(search_end_bracket);

        if (found_begin != std::string::npos) {
          int legnth_to_save = found_end - (found_begin + size_search_d);
          std::string transformed_value = value;

          ref_name = value.substr(found_begin + size_search_d, legnth_to_save);
          int only_ref_complete = (search_dollar_begin_bracket + ref_name + search_end_bracket).size();

          std::string ref_value = dotenv::pre::usefile::found_value_of_reference(vector_of_future_env, ref_name);
          transformed_value.replace(found_begin, only_ref_complete, ref_value);
          std::map<std::string, std::string> map_for_insert{{key, transformed_value}};
          vector_of_future_env.push_back(map_for_insert);
          vector_of_future_env.erase(vector_of_future_env.begin() + index);
          break;
        }
      }
    }
  }

  inline void set_environment_with_preserve(std::vector<std::map<std::string, std::string>> vector_of_future_env) {
    for (auto vector : vector_of_future_env) {
      for (const auto &[key, value] : vector) {
        if (!(std::getenv(key.c_str()))) {
          dotenv::pre::common::set_environment(key.c_str(), value.c_str());
        }
      }
    }
  }

  inline void set_environment_without_preserve(std::vector<std::map<std::string, std::string>> vector_of_future_env) {
    for (auto vector : vector_of_future_env) {
      for (const auto &[key, value] : vector) {
        dotenv::pre::common::set_environment(key.c_str(), value.c_str());
      }
    }
  }
}