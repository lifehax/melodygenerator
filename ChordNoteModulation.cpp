#include "stdafx.h"

#include <vector>

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "ChordNoteModulation.h"
#include "WeightRandomChordGenerator.h"
#include "Chord.h"

ChordNoteModulation::ChordNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
}

void ChordNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	int rootNote = this->forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);
	int size = this->forMelody->getParam<int>(MelodyParameterType::SIZE);
	int upperLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	WeightRandomChordGenerator * chordGenerator = new WeightRandomChordGenerator(size);
	std::vector<std::string> * chords = chordGenerator->getChordPattern();
	int i = 0;
	for (auto note : *phraseNotes) {
		std::string chord = chords->at(i++);
		note->switchToChord(chord);
	}
}
