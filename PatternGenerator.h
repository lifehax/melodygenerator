#pragma once

#include <vector>

class PatternGenerator {
protected:
public:
	virtual std::vector<int> * getPattern() = 0;
};