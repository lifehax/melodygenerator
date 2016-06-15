#pragma once
#include "string"
#include "vector"
#include "stack"
#include <map>

class Generator {
protected:
	std::map<std::string, std::string> * optionValues;
public:
	void generate(int type);
	void setOptionValues(std::map<std::string, std::string> *);
};