#pragma once

#include "RangeIntervalMelody.h"
#include <functional>

class FunctionRandomRangeIntervalMelody : public RangeIntervalMelody {
protected:
	std::function<int(int)> * directionFunction;
	std::function<int(int)> * upwardsLengthFunction;
	std::function<int(int)> * downwardsLengthFunction;
public:
	void setDirectionFunction(std::function<int(int)> *);
	void setUpwardsLengthFunction(std::function<int(int)> *);
	void setDownwardsLengthFunction(std::function<int(int)> *);

};