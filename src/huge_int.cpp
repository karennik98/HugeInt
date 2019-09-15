#include "../include/huge_int.h"

#include <tuple>
#include <iostream>
#include <regex>

HugeInt::HugeInt(std::string digits)
    : m_digits(digits)
{
    if(!is_valid_number_format())
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


HugeInt HugeInt::operator +(const HugeInt& rhs)
{
    if(m_sign == false && rhs.m_sign == true)
    {
        HugeInt number = rhs;
        number.m_sign = false;
        return *this - number;
    }
    else if(this->m_sign == true && rhs.m_sign == false)
    {
        HugeInt number = *this;
        number.m_sign = false;
        return -(number - rhs);
    }
    bool sign = false;
    if (m_sign == true && rhs.m_sign == true)
    {
        sign = true;
    }
    std::string larger, smaller;
    std::tie(larger,smaller) = get_larger_and_smaller(this->m_digits, rhs.m_digits);
    std::string sum = larger;
	int diffInLenghts = larger.size()-smaller.size();
	smaller.insert(0,diffInLenghts,'0');
	for (int i = smaller.size() - 1; i >= 0; --i)
	{
		sum[i] = ((smaller[i] - '0') + (larger[i] - '0') + '0');
		if (i != 0)
		{
			if (sum[i] > '9')
			{
				sum[i] -= 10;
				smaller[i - 1] += 1;
			}
		}
	}
	if (sum[0] > '9')
	{
		sum[0] -= 10;
		sum.insert(0, 1, '1');
	}
    HugeInt result(sum);
    result.set_sign(sign);
    return result;
}

HugeInt HugeInt::operator -(const HugeInt& rhs)
{
    if(this->m_sign == false && rhs.m_sign == true)
    {
        HugeInt number = rhs;
        number.m_sign = false; 
        return *this + number;
    }
    else if ( this->m_sign == true && rhs.m_sign== false)
    {
        HugeInt number = *this;
        number.m_sign = false;
        return -(number + rhs);
    }
    bool sign = false;
    std::string larger, smaller;
    std::tie(larger, smaller) = get_larger_and_smaller(this->m_digits, rhs.m_digits);
    if(m_sign == false && rhs.m_sign == false && larger == rhs.m_digits || m_sign == true && rhs.m_sign == true && larger == m_digits)
        sign = true;
    //std::string quotient = larger;
    HugeInt result(larger);
    size_t diff = larger.size()-smaller.size();
    smaller.insert(0,diff,'0');
    for(int i = larger.size()-1; i>=0; --i)
    {
        if(larger[i] < smaller[i])
        {
            larger[i] += 10;
            larger[i-1] -= 1;
        }
        result.m_digits[i] = ((larger[i] - '0') - (smaller[i] - '0') + '0');
    }
    while(result.m_digits[0] == '0' && result.m_digits.length() != 1)
    {
        result.m_digits.erase(0,1);
    }
    result.set_sign(sign);
    return result;
}
HugeInt HugeInt::operator *(const HugeInt& rhs)
{
    bool sign = true;
    if((m_sign == false && rhs.m_sign == false) || (m_sign == true && rhs.m_sign == true))
    {
        sign = false;
    }
    size_t len1 = m_digits.size(); 
    size_t len2 = rhs.m_digits.size(); 
    if (len1 == 0 || len2 == 0) 
    {
        return HugeInt("0"); 
    }

    std::vector<int> result_vec(len1 + len2, 0); 
  
    size_t i_n1 = 0;  
    size_t i_n2 = 0;  
       
    for (int i=len1-1; i>=0; i--) 
    { 
        int carry = 0; 
        int n1 = m_digits[i] - '0'; 
  
        i_n2 = 0;  
            
        for (int j=len2-1; j>=0; j--) 
        { 
            int n2 = rhs.m_digits[j] - '0'; 
            int sum = n1*n2 + result_vec[i_n1 + i_n2] + carry; 
            carry = sum/10; 

            result_vec[i_n1 + i_n2] = sum % 10; 
  
            i_n2++; 
        } 
  
        if (carry > 0) 
        {
            result_vec[i_n1 + i_n2] += carry; 
        }
        i_n1++; 
    } 

    int i = result_vec.size() - 1; 
    while (i>=0 && result_vec[i] == 0) 
    {
        i--;
    } 

    if (i == -1) 
    {
        return HugeInt("0"); 
    }

    HugeInt result;
    while (i >= 0) 
    {
        result.m_digits += std::to_string(result_vec[i--]); 
    }
    result.set_sign(sign);
    return result;
}

HugeInt HugeInt::operator /(const HugeInt& rhs)
{
    if(rhs.m_digits == "0")
    {
        throw DivideByZero("divide by zero", "huge_int.cpp", "operator /(const HugeInt& rhs)",150);
    }
    if(m_digits == "0")
    {
        return HugeInt("0");
    }

    HugeInt copy_this = *this;
    HugeInt copy_rhs = rhs;
    bool sign = true;

    if(!copy_this.is_negative() && !copy_rhs.is_negative() || copy_this.is_negative() && copy_rhs.is_negative())
    {
        sign = false;
    }

    copy_rhs.set_sign(false);
    copy_this.set_sign(false);
    HugeInt quotient("0");
    while(copy_this >= copy_rhs)
    {
        copy_this -=  copy_rhs;
        ++quotient;
    }
    if(quotient.m_digits != "0")
        quotient.set_sign(sign);
    return quotient;
}

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

std::pair<std::string, std::string> HugeInt::get_larger_and_smaller(std::string first, std::string second)const 
{
    std::string larger = first.length() > second.length() ? first : second;
    std::string smaller = first != larger ? first : second;
    return std::make_pair(larger, smaller); 
}

HugeInt HugeInt::operator++()
{
    return *this = std::move(*this + HugeInt("1"));
}

HugeInt& HugeInt::operator-=(const HugeInt& other)
{
    return *this = std::move(*this - other);
}

std::ostream& operator<<(std::ostream& out, const HugeInt& number)
{
    if(number.m_sign == true)
        out<<'-';
    out<<number.m_digits;
    return out;
}

bool HugeInt::is_valid_number_format()const
{
    std::regex reg1("[0-9]*");
    std::regex reg2("-[0-9]*");
    return std::regex_match(m_digits, reg1) || std::regex_match(m_digits, reg2);
}
