#include "../include/huge_int.h"

bool HugeInt::operator >(const HugeInt& other)const
{
	bool other_sign = other.get_sign();
	if (!(m_sign && other_sign))
	{
		if (m_digits.length() > other.m_digits.length())
		{
			return true;
		}
		else if (m_digits.length() < other.m_digits.length())
		{
			return false;
		}
		else if (m_digits.length() == other.m_digits.length())
		{
			for (int i = 0; i < m_digits.length(); ++i)
			{
				if (m_digits[i] > other.m_digits[i])
				{
					return true;
				}
				else if (m_digits[i] < other.m_digits[i])
				{
					return false;
				}
			}
		}
	}
	else if (m_sign && other_sign)
	{
		if (m_digits.length() < other.m_digits.length())
		{
			return true;
		}
		else if (m_digits.length() > other.m_digits.length())
		{

			return false;
		}
		else if (m_digits.length() == other.m_digits.length())
		{
			for (int i = 0; i < m_digits.length(); ++i)
			{
				if (m_digits[i] < other.m_digits[i])
				{
					return true;
				}
				else if (m_digits[i] > other.m_digits[i])
				{
					return false;
				}
			}
		}
	}
	else if (m_sign)
		return true;
	else if (other_sign)
		return false;
}
bool HugeInt::operator ==(const HugeInt& other)const
{
    return(m_digits == other.m_digits && m_sign == other.m_sign);
}

bool HugeInt::HugeInt::operator >=(const HugeInt& other)const
{
    return (*this > other || *this == other);
}