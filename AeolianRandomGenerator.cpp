#include "stdafx.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

#include "AeolianRandomGenerator.h"
#include "NaturalMinorScale.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"

#include <algorithm>
#include <functional>

AeolianRandomGenerator::AeolianRandomGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
}

void AeolianRandomGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));
	srand((unsigned int)time(NULL));
	NaturalMinorScale scale;

	std::vector<std::string> chordProgression = {
		"i", "v", "i", "iv", "i", "v", "I"
	};

	std::vector<std::string> bassChordProgression = {
		"iv", "iv", "iv", "iv"
	};

	std::vector<int> * bassNotes = scale.getNotes(33);
	std::vector<int> * notes = scale.getNotes(57);
	std::vector<int> * trebleNotes = scale.getNotes(81);
	int numChords = chordProgression.size();

	int trebleNote = 0;
	int newTrebleNoteIdx = 0;

	int bassNote = 0;
	int newBassNoteIdx = 0;

	int currentNote = 0;

	int currentChord = 0;
	int currentBassChord = -1;

	for (int beatPosition = 0; beatPosition < this->type->getSongLength(); beatPosition++) {

		if (currentChord == chordProgression.size()) {
			if (currentChord >= 0) {
				this->target->addItem(TrackItem::CreateNote(beatPosition * type->getMicroSecondsPerNote(), 108, type->getMicroSecondsPerNote()));
			}
		}

		if (currentChord % 2 == 0 || currentChord == chordProgression.size()) {
			int chordLength = currentChord == chordProgression.size() ? 1 : 2;
			newBassNoteIdx = newBassNoteIdx + ((rand() % 3) - 1);
			if (newBassNoteIdx >= (int)bassNotes->size()) {
				newBassNoteIdx = (int)bassNotes->size() - 1;
			}
			else if (newBassNoteIdx < 0) {
				newBassNoteIdx = 0;
			}

			if (currentBassChord < 0 || currentBassChord == bassChordProgression.size()) {
				currentBassChord = 0;
			}

			bassNote = bassNotes->at(newBassNoteIdx);

			std::vector<std::pair<int, bool>> * bassChordNotes = Chord::GetChord(bassChordProgression[currentBassChord], bassNote);
			for (auto chordIt = bassChordNotes->begin(); chordIt != bassChordNotes->end(); ++chordIt) {
				this->target->addItem(TrackItem::CreateNote(beatPosition * type->getMicroSecondsPerNote(), (*chordIt).first, type->getMicroSecondsPerNote() * chordLength));
			}
			currentBassChord++;
		}

		if (currentChord == chordProgression.size()) {
			currentChord = 0;
		}

		currentNote = currentNote + ((rand() % 3) - 1);
		if (currentNote >= (int)notes->size()) {
			currentNote = (int)notes->size() - 1;
		}
		else if (currentNote < 0) {
			currentNote = 0;
		}

		int noteNumber = notes->at(currentNote);

		std::vector<std::pair<int, bool>> * chordNotes = Chord::GetChord(chordProgression[currentChord], noteNumber);
		for (auto chordIt = chordNotes->begin(); chordIt != chordNotes->end(); ++chordIt) {
			this->target->addItem(TrackItem::CreateNote(beatPosition * type->getMicroSecondsPerNote(), (*chordIt).first, type->getMicroSecondsPerNote()));
		}

		newTrebleNoteIdx = newTrebleNoteIdx + ((rand() % 3) - 1);
		if (newTrebleNoteIdx >= (int)trebleNotes->size()) {
			newTrebleNoteIdx = (int)trebleNotes->size() - 1;
		} else if (newTrebleNoteIdx < 0) {
			newTrebleNoteIdx = 0;
		}

		trebleNote = trebleNotes->at(newTrebleNoteIdx);
		this->target->addItem(TrackItem::CreateNote(beatPosition * type->getMicroSecondsPerNote(), trebleNote, type->getMicroSecondsPerNote()));

		currentChord++;
	}
}