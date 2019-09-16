#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <exception>
#include <string>

class Exception : public std::exception
{
public:
	const char* what() const throw() = 0;
	Exception(std::string info, std::string file, std::string func, unsigned line) 
        : m_info(info)
		, m_file(file)
        , m_func(func)
        , m_line(line)
	{

	}
protected:
	std::string m_info;
	std::string m_file;
	std::string m_func;
	unsigned m_line;
};

class DivideByZero : public Exception 
{
public:
	DivideByZero(std::string info, std::string file, std::string func, unsigned line) : Exception(info, file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("info: " + m_info + "\nfile: " + m_file = "\nfunction: " + m_func + "\nline: " + std::to_string(m_line)).c_str();
	}
};

class InvalidNumberFormat : public Exception
{
public:
    InvalidNumberFormat(std::string info, std::string file, std::string func, unsigned line) : Exception(info, file, func, line)
	{
	}
	const char* what() const throw() override
	{
		return ("info: " + m_info + " file: " + m_file = " function: " + m_func + " line: " + std::to_string(m_line)).c_str();
	}
};

#endif