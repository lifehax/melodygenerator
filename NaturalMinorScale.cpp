#include "stdafx.h"

#include <vector>

#include "NaturalMinorScale.h"

std::vector<int> * NaturalMinorScale::getIntervals() {
	return new std::vector<int>({ 0, 2, 3, 5, 7, 8, 10 });
}

std::vector<std::string> * NaturalMinorScale::getModes() {
	return new std::vector<std::string>({ "A", "C" });
}

std::string NaturalMinorScale::getName() {
	return "Natural Minor";
}
