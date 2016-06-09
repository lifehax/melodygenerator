#pragma once

#include <functional>
#include "NoteModulation.h"


class PatternNoteModulation : public NoteModulation {
protected:
public:
	PatternNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
