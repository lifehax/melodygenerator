#pragma once
#include <vector>

#include "Scale.h"


class GMinorScale : public Scale {
public:
	virtual std::vector<int> *  getIntervals();
	virtual std::vector<std::string> * getModes();
};
