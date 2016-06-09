#pragma once

#include <functional>
#include "NoteModulation.h"
#include "ModulatorFunctions.h"

class Scale;

class FunctionNoteModulation : public NoteModulation {
protected:
	ModulatorFunction * withFunction;
public:
	FunctionNoteModulation(ModularMelody *);

	void modifyNotes(std::vector<TrackItem *> *);
};
