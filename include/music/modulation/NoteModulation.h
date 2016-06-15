#pragma once

#include <vector>
#include "ModulatorFunctions.h"

class MIDITrack;
class TrackNote;
class ModularMelody;

class NoteModulation {
protected:
	MIDITrack * forTrack;
	ModularMelody * forMelody;

public:
	NoteModulation(ModularMelody *);

	virtual void modifyNotes(std::vector<TrackItem *> *) = 0;
};

#include "FunctionNoteModulation.h"
#include "ScaleNoteModulation.h"
#include "PatternNoteModulation.h"
#include "RandomNoteModulation.h"
#include "RandomShiftNoteModulation.h"
#include "ChordNoteModulation.h"
