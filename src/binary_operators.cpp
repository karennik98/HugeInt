#include "../include/huge_int.h"

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
    std::tie(larger,smaller) = utility::get_larger_and_smaller(this->m_digits, rhs.m_digits);

	int diff = larger.size()-smaller.size();
	smaller.insert(0,diff,'0');

    std::string sum = larger;
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

    std::string larger, smaller;
    std::tie(larger, smaller) = utility::get_larger_and_smaller(this->m_digits, rhs.m_digits);

    bool sign = false;
    if(m_sign == false && rhs.m_sign == false && larger == rhs.m_digits || m_sign == true && rhs.m_sign == true && larger == m_digits)
    {
        sign = true;
    }

    size_t diff = larger.size()-smaller.size();
    smaller.insert(0,diff,'0');

    HugeInt result(larger);
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
    {
        quotient.set_sign(sign);
    }
    
    return quotient;
}