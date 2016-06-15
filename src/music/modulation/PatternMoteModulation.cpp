#include "stdafx.h"

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "PatternNoteModulation.h"

PatternNoteModulation::PatternNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
}

void PatternNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	std::vector<int> * pattern = this->forMelody->getParam<std::vector<int> *>(MelodyParameterType::MODULATION_PATTERN);
	int rootNote = this->forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);
	int upperLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	int i = 0;
	for (auto note : *phraseNotes) {
		int newNote = rootNote + (*pattern)[i % pattern->size()];
		if (newNote > upperLimit) {
			newNote = upperLimit;
		} else if (newNote < lowerLimit) {
			newNote = lowerLimit;
		}
		note->setNoteByNumber(newNote);
		i++;
	}
}
