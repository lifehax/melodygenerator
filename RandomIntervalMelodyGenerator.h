#pragma once
#include <vector>

#include "SongGenerator.h"
#include "RangeIntervalMelody.h"

class Type;

class RandomIntervalMelodyGenerator : public SongGenerator {
protected:
	RangeIntervalMelody * midRangeMelody;
	RangeIntervalMelody * midRangeUpperMelody;
	RangeIntervalMelody * midRangeLowerMelody;
	RangeIntervalMelody * trebleMelody;
	RangeIntervalMelody * bassMelody;
public:
	RandomIntervalMelodyGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};