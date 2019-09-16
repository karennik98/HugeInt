#pragma once

#include "exception.h"
#include "utility.h"

#include <vector>
#include <string>
#include <regex>

#define MAX_DIGITS_SIZE 30

class HugeInt
{
public:
    HugeInt(std::string digits="");
    HugeInt(const HugeInt& other);
    HugeInt(HugeInt&& other);
    //HugeInt(const std::string& other);
public:
    HugeInt operator +(const HugeInt& rhs);
    HugeInt operator -(const HugeInt& rhs);
    HugeInt operator *(const HugeInt& rhs);
    HugeInt operator /(const HugeInt& rhs);

    HugeInt& operator=(const HugeInt& other);
    HugeInt& operator=(HugeInt&& other);
    HugeInt& operator=(const std::string& other);

    HugeInt operator-() const;

    HugeInt& operator++();
    const HugeInt operator++(int);

    bool operator >(const HugeInt& other)const;
    bool operator ==(const HugeInt& other)const;
    bool operator >=(const HugeInt& other)const;

    HugeInt& operator-=(const HugeInt& other);

    friend std::ostream& operator<<(std::ostream& out,  const HugeInt& number);
public:
    void set_sign(bool sign)
    {
        m_sign = sign;
    }
    bool get_sign()const
    {
        return m_sign;
    }
private:
    HugeInt inverse();
    bool is_negative()const
    {
        return (m_sign == true);
    }
private:
    std::string m_digits;
    bool m_sign = false;
};
