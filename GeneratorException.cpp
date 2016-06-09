#include "stdafx.h"
#include "GeneratorException.h"

GeneratorException::GeneratorException(char * str) {
	this->exceptionStr = str;
}

GeneratorException::~GeneratorException() {
	delete this->exceptionStr;
}

const char * GeneratorException::what() {
	return this->exceptionStr;
}
