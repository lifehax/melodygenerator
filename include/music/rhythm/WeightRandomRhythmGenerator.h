#pragma once

#include "RhythmGenerator.h"

class WeightRandomRhythmGenerator : public RhythmGenerator {
protected:
	std::map<float, int> noteLengthWeightMap;
public:
	WeightRandomRhythmGenerator(double, int);
	void setWeightMap(std::map<float, int> noteLengthWeight);
	std::vector<float> * getRhythm();
};
