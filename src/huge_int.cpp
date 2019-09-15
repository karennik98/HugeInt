#include "../include/huge_int.h"
#include "../include/utility.h"

#include <tuple>
#include <iostream>
#include <regex>

HugeInt::HugeInt(std::string digits)
    : m_digits(digits)
{
    if(!utility::is_valid_number_format(m_digits))
    {
        throw InvalidNumberFormat("invalid number format", "huge_int.cpp", "HugInt(std::string, bool sign)", 10);
    }
    if(m_digits[0] == '-')
    {
        m_sign = true;
        m_digits.erase(0,1);
    }
    else
    {
        m_sign = false;
    }
}

HugeInt::HugeInt(const HugeInt& other)
{
    m_digits = other.m_digits;
    m_sign = other.m_sign;
}

HugeInt::HugeInt(HugeInt&& other)
{
    m_digits = other.m_digits;
    m_sign = other.m_sign;
    other.m_sign = false;
    other.m_digits="";
}

// HugeInt::HugeInt(const std::string& other)
// {
//     if(other[0] == '-')
//     {
//         m_digits = other;
//         m_sign = true;
//     }
//     else
//     {
//         m_digits = other;
//         m_sign = false;
//     }
// }


HugeInt HugeInt::inverse()
{
    if(this->m_digits[0] == '-')
    {
        this->m_digits.erase(0,1);
    }
    else
    {
        this->m_digits.insert(this->m_digits.begin(), '-');
    }
    return *this;
}

