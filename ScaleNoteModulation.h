#pragma once

#include <functional>
#include "NoteModulation.h"

class Scale;

class ScaleNoteModulation : public NoteModulation {
protected:
	Scale * withScale;
public:
	ScaleNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
