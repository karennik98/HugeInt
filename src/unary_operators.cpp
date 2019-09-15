#include "../include/huge_int.h"

HugeInt HugeInt::operator-() const
{
    HugeInt tmp;
    tmp.m_digits = m_digits;
    if(m_digits != "0")
    {
        if(m_sign == false)
        {
            tmp.m_sign = true;
            tmp.m_digits.insert(tmp.m_digits.begin(),'-');
        }
        else
        {
            tmp.m_sign = false;
            tmp.m_digits.erase(0,1);
        }
    }
    return tmp;
}