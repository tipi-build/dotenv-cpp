#include <fstream>
 #include <string>
 #include <stdlib.h>
 #include <utility>
 #include <dotenv/detail/common/common.hpp>

namespace dotenv::detail::usefile {

  inline bool is_multi_line_env(std::string line, std::string &key_multiline, bool multi_line) {
    if (!(multi_line)) {
      std::string search_equal_quote = R"(=")";
      std::size_t found = line.find(search_equal_quote);
        if (found != std::string::npos) {
          multi_line = true;
          key_multiline = line.substr(0, found);
        }
      }
    return multi_line;
  }

  inline bool is_end_of_multi_line_env(std::string line) {
    bool multi_line = false;
    int line_size = line.size();
    if (line[line_size - 1] == '"') {
      multi_line = true;
    }
    return multi_line;
  }

  inline std::pair<std::string, std::string> parse_file_string(std::string line) {
    std::string search_equal = "=";
    std::size_t found = line.find(search_equal);
    std::string key = "";
    std::string value = "";
    int size_line = line.size();

    if (found != std::string::npos) {
      key = line.substr(0, found);
      value = line.substr(found + 1, size_line);
      if ((line[size_line-1]=='\r')){
        value.resize(value.size()-1);
      }      
    }

    std::pair<std::string, std::string> string_parse{key, value};
    return string_parse;
  }

  inline std::string value_begin_multi_line(std::string line) {
    std::string search_equal_quote = R"(=")";
    std::size_t found = line.find(search_equal_quote);
    int size_line = line.size();
    std::string value = line.substr(found + 2, size_line);
    return value;
  }

  inline std::string value_end_multi_line(std::string line) {
    int size_line = line.size();
    line.resize(size_line - 1);
    return line;
  }


  inline std::map<std::string, std::string> read_file_dotenv(std::string path_filename){
    std::map<std::string, std::string> map_for_environment;
    std::fstream file(path_filename.c_str(), std::ios::binary | std::ios::in | std::ios::out);
    std::string line;
    bool is_multi_line = false;
    bool is_end_of_multi_line = false;
    std::string key_multi = "";
    std::string value_multi_line = "";

    while (std::getline(file, line)) {
      if (!(line[0] == '#')){
        is_multi_line = is_multi_line_env(line,key_multi,is_multi_line);
        is_end_of_multi_line = is_end_of_multi_line_env(line);
        if ((is_multi_line) && (!(is_end_of_multi_line))) {
          if (is_multi_line_env(line, key_multi, false)) {
            value_multi_line = value_begin_multi_line(line);
          } else {
            value_multi_line = value_multi_line + line ;
          }
        } else if (is_multi_line && is_end_of_multi_line) {
          value_multi_line = value_multi_line + value_end_multi_line(line);
          std::pair<std::string, std::string> pair_for_insert{key_multi, value_multi_line};
          map_for_environment.insert(pair_for_insert);
          key_multi = "";
          value_multi_line = "";
          is_multi_line = false;
        } else {
          std::pair<std::string, std::string>pair_for_insert = parse_file_string(line);
          map_for_environment.insert(pair_for_insert);
        }
      }
    }
    return map_for_environment;
  }

}