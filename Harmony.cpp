#include "stdafx.h"
#include "Harmony.h"

Harmony::Harmony(MIDITrack * forTrack, std::vector<Harmony::HarmonyType> harmonizeAs) {
	this->forTrack = forTrack;
	this->harmonizeAs = harmonizeAs;
	this->harmonizeWithAtTime = NULL;
}

bool Harmony::isHarmonicWithTime(int note, int64_t trackTime) {
	if (this->currentTimeCache != trackTime || this->harmonizeWithAtTime == NULL) {
		this->harmonizeWithAtTime = this->forTrack->getNotesAtTime(trackTime);
	}
	return this->isHarmonicWithNotesAtTime(note, this->harmonizeWithAtTime);
}

bool Harmony::isHarmonicWithNotesAtTime(int note, std::vector<TrackItem *> * harmonizeWith) {
	bool isInHarmony = true;
	for (auto with : *harmonizeWith) {
		bool isNoteInAHarmony = false;
		for (Harmony::HarmonyType as : this->harmonizeAs) {
			if (as == Harmony::HarmonyType::NOT_SAME_NOTE && note == with->getNumber()) {
				isNoteInAHarmony = false;
				break;
			} else if (!isNoteInAHarmony) {
				isNoteInAHarmony |= ((std::abs(note - with->getNumber()) % 12) == Harmony::intervalAmounts.at(as));
			}
		}
		isInHarmony &= isNoteInAHarmony;
	}
	return isInHarmony;
}

bool Harmony::isHarmonicWithNotes(TrackItem * note, std::vector<TrackItem *> * harmonizeWith) {
	bool isInHarmony = true;
	for (auto with : *harmonizeWith) {
		for (auto withSub: *(with->getAllNotes())) {
			bool isNoteInAHarmony = false;
			for (Harmony::HarmonyType as : this->harmonizeAs) {
				bool allNotesHaveHarmony = true;
				for(auto noteSub: *(note->getAllNotes())) {
					allNotesHaveHarmony &= ((std::abs(noteSub->getNumber() - withSub->getNumber()) % 12) == Harmony::intervalAmounts.at(as));
				}
				isNoteInAHarmony |= allNotesHaveHarmony;
				if (allNotesHaveHarmony) break;
			}
			isInHarmony &= isNoteInAHarmony;
		}
	}
	return isInHarmony;
}

const std::map<Harmony::HarmonyType, int> Harmony::intervalAmounts {
	{ Harmony::HarmonyType::MINOR_SECOND_INTERVAL, 1 },
	{ Harmony::HarmonyType::MAJOR_SECOND_INTERVAL, 2 },
	{ Harmony::HarmonyType::MINOR_THIRD_INTERVAL, 3 },
	{ Harmony::HarmonyType::MAJOR_THIRD_INTERVAL, 4 },
	{ Harmony::HarmonyType::PERFECT_FOURTH_INTERVAL, 5 },
	{ Harmony::HarmonyType::PERFECT_FIFTH_INTERVAL, 7 },
	{ Harmony::HarmonyType::MINOR_SIXTH_INTERVAL, 8 },
	{ Harmony::HarmonyType::MAJOR_SIXTH_INTERVAL, 9 },
	{ Harmony::HarmonyType::MINOR_SEVENTH_INTERVAL, 10 },
	{ Harmony::HarmonyType::MAJOR_SEVENTH_INTERVAL, 11 },
	{ Harmony::HarmonyType::PERFECT_OCTAVE_INTERVAL, 0 },
	{ Harmony::HarmonyType::NOT_SAME_NOTE, -1 }
};