#include "stdafx.h"

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "RandomNoteModulation.h"

RandomNoteModulation::RandomNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
}

void RandomNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	int upperLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);

	for (auto note : *phraseNotes) {
		note->setNoteByNumber((rand() % (upperLimit - lowerLimit)) + lowerLimit);
	}
}
