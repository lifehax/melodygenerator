#pragma once

#include <functional>
#include "NoteModulation.h"


class LeadFollowNoteModulation : public NoteModulation {
protected:
public:
	LeadFollowNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
