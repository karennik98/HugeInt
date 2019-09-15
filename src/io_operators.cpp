#include "../include/huge_int.h"

std::ostream& operator<<(std::ostream& out, const HugeInt& number)
{
    if(number.m_sign == true)
        out<<'-';
    out<<number.m_digits;
    return out;
}