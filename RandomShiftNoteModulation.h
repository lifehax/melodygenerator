#pragma once

#include <functional>
#include "NoteModulation.h"

class Scale;

class RandomShiftNoteModulation : public NoteModulation {
protected:
	Scale * withScale;
public:
	RandomShiftNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
