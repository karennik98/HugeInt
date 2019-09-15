#include "../include/utility.h"

std::pair<std::string, std::string> utility::get_larger_and_smaller(std::string first, std::string second)
    {
        std::string larger = first.length() > second.length() ? first : second;
        std::string smaller = first != larger ? first : second;
        return std::make_pair(larger, smaller); 
    }


bool utility::is_valid_number_format(std::string number)
{
    std::regex reg1("[0-9]*");
    std::regex reg2("-[0-9]*");
    return std::regex_match(number, reg1) || std::regex_match(number, reg2);
}