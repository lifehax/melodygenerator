#pragma once

#include "NoteByNoteMelody.h"
#include <vector>

class RangeIntervalMelody : public NoteByNoteMelody {
public:
	enum class Direction { UP, SAME, DOWN };
	enum class HarmonyMode { WITH_CURRENT_TIME, NO_HARMONY };

protected:

	int amount;

	Harmony * harmony;
	RangeIntervalMelody::HarmonyMode harmonyMode;
	RangeIntervalMelody::Direction direction;
	int64_t currentTendencyStart;
	int currentTendencyAmount;

	bool forceNewDirection;
	std::vector<RangeIntervalMelody::Direction> directionTries;

	std::vector<float> rhythm;
	int currentRhythmStep;

	int upperNoteLimit;
	int lowerNoteLimit;

	double upwardsTendencyLengthLowerLimit;
	double upwardsTendencyLengthUpperLimit;
	int upwardsTendencyAmountLowerLimit;
	int upwardsTendencyAmountUpperLimit;

	double downwardsTendencyLengthLowerLimit;
	double downwardsTendencyLengthUpperLimit;
	int downwardsTendencyAmountLowerLimit;
	int downwardsTendencyAmountUpperLimit;

	double sameTendencyLengthLowerLimit;
	double sameTendencyLengthUpperLimit;

public:
	RangeIntervalMelody(MIDITrack *);
	virtual void addMelodyAtTime(int64_t trackTime);

	void setUpwardsTendencyLengthRange(double, double);
	void setDownwardsTendencyLengthRange(double, double);
	void setUpwardsTendencyAmountRange(int, int);
	void setDownwardsTendencyAmountRange(int, int);
	void setSameTendencyLengthRange(double, double);
	void setNoteLimits(int, int);

	void setDirection();
	void setAmount();
	void setRhythm(std::vector<float> rhythm);

	RangeIntervalMelody * setHarmony(Harmony * harmony);
	Harmony * getHarmony();
	bool shouldHarmonizeWithTime();
};

