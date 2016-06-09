#pragma once

#include "PatternGenerator.h"

class RandomPatternGenerator : public PatternGenerator {
protected:
public:
	std::vector<int> * getPattern();
};
