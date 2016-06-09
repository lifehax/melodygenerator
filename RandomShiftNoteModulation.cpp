#include "stdafx.h"

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "RandomShiftNoteModulation.h"

RandomShiftNoteModulation::RandomShiftNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
}

void RandomShiftNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	int upperLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	int maxShift = this->forMelody->getParamDefault<int>(MelodyParameterType::MAX_SHIFT, 5);

	TrackItem * previousNote = NULL;
	for (auto note : *phraseNotes) {
		if (previousNote == NULL) {
			note->setNoteByNumber((rand() % (upperLimit - lowerLimit)) + lowerLimit);
		} else {
			int prevNoteNumber = previousNote->getNumber();
			int max = prevNoteNumber + maxShift;
			if (max > upperLimit) max = upperLimit;
			int min = prevNoteNumber - maxShift;
			if (min < lowerLimit) min = lowerLimit;
			note->setNoteByNumber((rand() % (max - min)) + min);
		}
		previousNote = note;
	}
}
