#pragma once

#include "RhythmGenerator.h"

class RandomRhythmGenerator : public RhythmGenerator {
protected:
public:
	RandomRhythmGenerator(double, int);
	std::vector<float> * getRhythm();
};
