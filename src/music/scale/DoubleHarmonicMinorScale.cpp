#include "stdafx.h"

#include <vector>

#include "DoubleHarmonicMinorScale.h"

std::vector<int> * DoubleHarmonicMinorScale::getIntervals() {
	return new std::vector<int>({ 0, 2, 3, 6, 7, 8, 11 });
}

std::vector<std::string> * DoubleHarmonicMinorScale::getModes() {
	return new std::vector<std::string>({ "Eb", "C", "A" });
}

std::string DoubleHarmonicMinorScale::getName() {
	return "Double Harmonic Minor";
}
