#pragma once

#include <vector>

class RhythmGenerator {
protected:
	double notesPerBar;
	int noteDivision;
public:
	RhythmGenerator(double, int);
	virtual std::vector<float> * getRhythm() = 0;
};
