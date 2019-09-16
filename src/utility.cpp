#include "../include/utility.h"

std::pair<std::string, std::string> utility::get_larger_and_smaller(std::string first, std::string second)
{
    std::string larger, smaller;
    if(first.length() == second.length())
    {
        if(first == second)
        {
            return std::make_pair(first,second);
        }
        for(int i=0;i<first.length();++i)
        {
            if(first[i]>second[i])
            {
                larger = first;
                smaller = second;
                break;
            }
            else if(first[i]<second[i])
            {
                larger = second;
                smaller = first;
                break;
            }
        }
    }
    else
    {
        larger = first.length() > second.length() ? first : second;
        smaller = first != larger ? first : second;
    }
    return std::make_pair(larger, smaller); 
}

bool utility::is_valid_number_format(std::string number)
{
    std::regex reg1("[0-9]*");
    std::regex reg2("-[0-9]*");
    return std::regex_match(number, reg1) || std::regex_match(number, reg2);
}