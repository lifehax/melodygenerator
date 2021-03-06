#pragma once
#include <vector>

#include "Scale.h"


class NaturalMinorScale : public Scale {
public:
	virtual std::vector<int> *  getIntervals();
	virtual std::vector<std::string> * getModes();
	virtual std::string getName();
};
