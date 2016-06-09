#pragma once

#include "Melody.h"
#include <vector>


class ExponentialDecayMelody : public Melody {
protected:
	int numNotes;
	int rate;

public:
	ExponentialDecayMelody();
	virtual std::vector<TrackNote *> * getNotes(int trackTime, std::vector<TrackNote *> * mustHarmonizeWith);
};