#pragma once

#include <functional>
#include "NoteModulation.h"


class ChordNoteModulation : public NoteModulation {
protected:
public:
	ChordNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
