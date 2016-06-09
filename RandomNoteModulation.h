#pragma once

#include <functional>
#include "NoteModulation.h"

class Scale;

class RandomNoteModulation : public NoteModulation {
protected:
	Scale * withScale;
public:
	RandomNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
