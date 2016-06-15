#include "stdafx.h"

#include <algorithm>

#include "Track.h"
#include "NoteModulation.h"
#include "ConnectedHarmonyMelody.h"
#include "Chord.h"

ConnectedHarmonyMelody::ConnectedHarmonyMelody(MIDITrack * forTrack) : ModularMelody(forTrack) {
	this->connectedMelodies = new ConnectedMelodies();
}


ConnectedMelodies * ConnectedHarmonyMelody::getConnections() {
	connectedMelodies->insert_or_assign(this->getParam<int>(MelodyParameterType::PRIORITY), this);
	return this->connectedMelodies;
}

void ConnectedHarmonyMelody::setConnections(ConnectedMelodies * others) {
	others->insert_or_assign(this->getParam<int>(MelodyParameterType::PRIORITY), this);
	this->connectedMelodies = others;
}

void ConnectedHarmonyMelody::addAsPhrase() {
	ModularMelody::addAsPhrase();

	int64_t time = this->getParam<int64_t>(MelodyParameterType::TRACK_TIME);

	if (ConnectedHarmonyMelody::HarmonyMode::AFTER_ADD ==
		this->getParamDefault<ConnectedHarmonyMelody::HarmonyMode>(MelodyParameterType::HARMONY_MODE, ConnectedHarmonyMelody::HarmonyMode::AFTER_ADD)) {
		std::vector<std::string> * otherMelodies = new std::vector<std::string>();
		for (auto melody : *(this->connectedMelodies)) {
			if (melody.second->getUniqueName() != this->getUniqueName()) {
				otherMelodies->push_back(melody.second->getUniqueName());
			}
		}
		this->harmonize(otherMelodies);
	}
}

void ConnectedHarmonyMelody::harmonize(std::vector<std::string> * against) {
	std::vector<TrackItem *> * thisMelodyNotes = this->forTrack->getAllNotesForMelody(this->getUniqueName());
	Harmony * harmony = this->getParamDefaultFunc<Harmony *>(MelodyParameterType::HARMONIZER, [this](Melody * forMelody)->Harmony * {
		return new Harmony(this->getTrack(), {
			Harmony::HarmonyType::PERFECT_FIFTH_INTERVAL,
			Harmony::HarmonyType::MAJOR_THIRD_INTERVAL,
			Harmony::HarmonyType::MAJOR_SIXTH_INTERVAL,
			Harmony::HarmonyType::PERFECT_FOURTH_INTERVAL,
			Harmony::HarmonyType::MINOR_THIRD_INTERVAL,
			Harmony::HarmonyType::MINOR_SIXTH_INTERVAL,
			Harmony::HarmonyType::PERFECT_OCTAVE_INTERVAL,
			Harmony::HarmonyType::NOT_SAME_NOTE
		});
	});


	int upperLimit = this->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	ChordReharmonizeMode chordHarmonyMode = this->getParamDefault<ChordReharmonizeMode>(MelodyParameterType::CHORD_REHARMONIZE_MODE, ChordReharmonizeMode::RANDOM);

	for (auto note: *thisMelodyNotes) {
		std::vector<TrackItem *> * otherMelodyNotes = this->forTrack->getNotesAtTimeForMelodies(note->getTrackTime(), against);

		if (!harmony->isHarmonicWithNotes(note, otherMelodyNotes)) {
			bool foundHarmonic = false;
			int numProcessed = 0;
			int currentDifference = 1;
			int original = note->getNumber();
			std::string originalDegree = "";
			bool chordReharmonize = false;
			std::vector<std::string> * chordTries = NULL;

			if (chordHarmonyMode == ChordReharmonizeMode::RANDOM && note->isChord()) {
				chordReharmonize = true;
				originalDegree = note->getObject<TrackChord>()->getDegree();
			}
			do {
				numProcessed = 0;
				if (original + currentDifference <= upperLimit) {
					if (chordReharmonize) {
						chordTries = new std::vector<std::string>(Chord::Chords);
						std::random_shuffle(chordTries->begin(), chordTries->end());
					}
					bool checkAllChords = true;
					do {
						note->setNoteByNumber(original + currentDifference);
						if (harmony->isHarmonicWithNotes(note, otherMelodyNotes)) {
							foundHarmonic = true;
							break;
						}
						if (chordReharmonize) {
							if (chordTries->size() == 0) {
								checkAllChords = false;
								note->getObject<TrackChord>()->setDegree(originalDegree);
							} else {
								note->getObject<TrackChord>()->setDegree(chordTries->back());
								chordTries->pop_back();
							}
						} else {
							checkAllChords = false;
						}
					} while (checkAllChords);
					numProcessed++;
				}
				if (original - currentDifference >= lowerLimit) {
					if (chordReharmonize) {
						chordTries = new std::vector<std::string>(Chord::Chords);
						std::random_shuffle(chordTries->begin(), chordTries->end());
					}
					bool checkAllChords = true;
					do {
						note->setNoteByNumber(original - currentDifference);
						if (harmony->isHarmonicWithNotes(note, otherMelodyNotes)) {
							foundHarmonic = true;
							break;
						}
						if (chordReharmonize) {
							if (chordTries->size() == 0) {
								checkAllChords = false;
								note->getObject<TrackChord>()->setDegree(originalDegree);
							} else {
								note->getObject<TrackChord>()->setDegree(chordTries->back());
								chordTries->pop_back();
							}
						} else {
							checkAllChords = false;
						}
					} while (checkAllChords);
					numProcessed++;
				}
				currentDifference++;
			} while (!foundHarmonic && numProcessed != 0);

			if (!foundHarmonic) {
				this->forTrack->removeItem(note);
			}
		}
	}
}

void ConnectedMelodies::harmonize(std::vector<std::string> * otherMelodies) {
	for (auto melody : *(this)) {
		if (std::find(otherMelodies->begin(), otherMelodies->end(), melody.second->getUniqueName()) != otherMelodies->end()) {
			melody.second->harmonize(otherMelodies);
		}
	}
}

void ConnectedMelodies::harmonize() {
	std::vector<std::string> * otherMelodies = new std::vector<std::string>();

	for (auto melody : *(this)) {
		melody.second->harmonize(otherMelodies);
		otherMelodies->push_back(melody.second->getUniqueName());
	}
}
