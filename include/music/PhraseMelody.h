#pragma once

#include "Melody.h"

class PhraseMelody : public Melody {
protected:
public:
	PhraseMelody(MIDITrack *);

	virtual void addAsPhrase() = 0;
	int getPhraseLength();
	int getMelodyRepeatLength();
	int64_t getFinishTime();
};
