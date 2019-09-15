#pragma once
#include <string>
#include <regex>

namespace utility {

    std::pair<std::string, std::string> get_larger_and_smaller(std::string first, std::string second);
    
    bool is_valid_number_format(std::string number);
}