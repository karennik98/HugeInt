#include "../include/huge_int.h"

HugeInt& HugeInt::operator=(const HugeInt& other)
{
    if(this == &other)
    {
        return *this;
    }

    m_digits = other.m_digits;
    m_sign = other.m_sign;
    return *this;
}

HugeInt& HugeInt::operator=(const std::string& other)
{
    m_digits = other;
    if(m_digits[0] == '-')
    {
        m_sign = true;
    }
    return *this;
}

HugeInt& HugeInt::operator=(HugeInt&& other)
{
    if(this == &other)
    {
        return *this;
    }
    m_sign = other.m_sign;
    m_digits = other.m_digits;
    other.m_sign = false;
    other.m_digits = "";
}

HugeInt& HugeInt::operator-=(const HugeInt& other)
{
    return *this = std::move(*this - other);
}