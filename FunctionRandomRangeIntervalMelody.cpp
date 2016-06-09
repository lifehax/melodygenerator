#include "stdafx.h"

#include <iostream>
#include "FunctionRandomRangeIntervalMelody.h"

void FunctionRandomRangeIntervalMelody::setDirectionFunction(std::function<int(int)> * function) {
	this->directionFunction = function;
}

void FunctionRandomRangeIntervalMelody::setUpwardsLengthFunction(std::function<int(int)> * function) {
	this->upwardsLengthFunction = function;
}

void FunctionRandomRangeIntervalMelody::setDownwardsLengthFunction(std::function<int(int)> * function) {
	this->downwardsLengthFunction = function;
}