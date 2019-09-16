#include "../include/huge_int.h"

HugeInt& HugeInt::operator++()
{
    *this = *this + HugeInt("1");
    return *this;
}

const HugeInt HugeInt::operator++(int)
{
    HugeInt tmp = *this;
    ++*this;
    return tmp;
}