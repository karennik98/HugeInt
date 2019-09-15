#include "../include/huge_int.h"

HugeInt HugeInt::operator++()
{
    return *this = std::move(*this + HugeInt("1"));
}