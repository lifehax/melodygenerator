#pragma once

#include <exception>

class GeneratorException : public std::exception {
protected:
	char * exceptionStr;
public:
	GeneratorException(char * str);
	~GeneratorException();
	const char * what();
};