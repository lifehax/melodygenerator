#include "stdafx.h"

#include <iostream>
#include "RangeIntervalMelody.h"
#include "TrackNote.h"
#include <fstream>
#include <time.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>

RangeIntervalMelody::RangeIntervalMelody(MIDITrack * forTrack) : NoteByNoteMelody(forTrack) {
	this->currentTendencyAmount = 0;
	this->currentTendencyStart = 0;
	this->forceNewDirection = false;
	this->currentRhythmStep = 0;
	this->harmonyMode = RangeIntervalMelody::HarmonyMode::WITH_CURRENT_TIME;
	this->harmony = new Harmony(forTrack, {
		Harmony::HarmonyType::MAJOR_THIRD_INTERVAL,
		Harmony::HarmonyType::PERFECT_FIFTH_INTERVAL,
		Harmony::HarmonyType::MAJOR_SIXTH_INTERVAL,
		Harmony::HarmonyType::PERFECT_OCTAVE_INTERVAL,
		Harmony::HarmonyType::NOT_SAME_NOTE
	});
}

void  RangeIntervalMelody::setUpwardsTendencyLengthRange(double lower, double upper) {
	this->upwardsTendencyLengthLowerLimit = lower;
	this->upwardsTendencyLengthUpperLimit = upper;
}

void  RangeIntervalMelody::setDownwardsTendencyLengthRange(double lower, double upper) {
	this->downwardsTendencyLengthLowerLimit = lower;
	this->downwardsTendencyLengthUpperLimit = upper;
}

void  RangeIntervalMelody::setUpwardsTendencyAmountRange(int lower, int upper) {
	this->upwardsTendencyAmountLowerLimit = lower;
	this->upwardsTendencyAmountUpperLimit = upper;
}

void  RangeIntervalMelody::setDownwardsTendencyAmountRange(int lower, int upper) {
	this->downwardsTendencyAmountLowerLimit = lower;
	this->downwardsTendencyAmountUpperLimit = upper;
}

void  RangeIntervalMelody::setSameTendencyLengthRange(double lower, double upper) {
	this->sameTendencyLengthLowerLimit = lower;
	this->sameTendencyLengthUpperLimit = upper;
}

void RangeIntervalMelody::setNoteLimits(int lower, int upper) {
	this->lowerNoteLimit = lower;
	this->upperNoteLimit = upper;
}

void RangeIntervalMelody::addMelodyAtTime(int64_t trackTime) {
	if (this->isReadyForNote(trackTime)) {
		TrackItem * newNote = NULL;
		int rootNote = this->getParam<int>(MelodyParameterType::ROOT_NOTE);
		int quarterNoteMicroSeconds = this->getParam<int>(MelodyParameterType::NOTE_LENGTH);
		std::string melodyGroup = this->getParamDefault<std::string>(MelodyParameterType::MELODY_GROUP, "");

		this->currTrackTime = trackTime;

		if (this->forTrack->size() == 0) {
			newNote = TrackItem::CreateNote(this->currTrackTime, rootNote, quarterNoteMicroSeconds);
			newNote->addMelody("rrim" + this->uniqueKey);
		} else {
			TrackNote * previousNote = this->forTrack->getMostRecentNoteForUniqueNoteMelody("rrim" + this->uniqueKey)->getObject<TrackNote>();
			if (this->currTrackTime >= previousNote->getLength() + previousNote->getTrackTime()) {
				this->setDirection();
				this->setAmount();

				if (this->amount != -1) {
					int step = this->amount * (this->direction == RangeIntervalMelody::Direction::UP ? 1 : this->direction == RangeIntervalMelody::Direction::DOWN ? -1 : 0);
					int thisNote = previousNote->getNumber() + step;

					newNote = TrackItem::CreateNote(this->currTrackTime, thisNote, quarterNoteMicroSeconds);
					newNote->addMelody("rrim" + this->uniqueKey);
					newNote->setMelodyGroup(melodyGroup);
				}
			}
		}

		if (newNote != NULL) {
			float noteFactor = this->rhythm[this->currentRhythmStep++];
			if (this->currentRhythmStep == this->rhythm.size()) {
				this->currentRhythmStep = 0;
			}
			newNote->setLength((int)(quarterNoteMicroSeconds * noteFactor));
			this->waitForNextNote(this->currTrackTime, newNote->getLength());
			this->forTrack->addItem(newNote);
		}
	}
}

void RangeIntervalMelody::setDirection() {
	int quarterNoteMicroSeconds = this->getParam<int>(MelodyParameterType::NOTE_LENGTH);
	if (this->currentTendencyStart + this->currentTendencyAmount <= this->currTrackTime || this->forceNewDirection) {
		this->forceNewDirection = false;
		int upperLimit = 2, lowerLimit = -2;
		TrackNote * previousNote = this->forTrack->getMostRecentNoteForUniqueNoteMelody("rrim" + this->uniqueKey)->getObject<TrackNote>();

		if (previousNote->getNumber() + this->upwardsTendencyAmountLowerLimit > this->upperNoteLimit) {
			upperLimit = 0;
		}

		if (previousNote->getNumber() - this->downwardsTendencyAmountLowerLimit < this->lowerNoteLimit) {
			lowerLimit = 0;
		}

		if (upperLimit == lowerLimit) {
			this->direction = RangeIntervalMelody::Direction::SAME;
		}
		else {
			int r = (rand() % ((upperLimit - lowerLimit) + 1)) + lowerLimit;
			this->direction = r < 0 ? RangeIntervalMelody::Direction::DOWN : r > 0 ? RangeIntervalMelody::Direction::UP : RangeIntervalMelody::Direction::SAME;
		}

		this->currentTendencyStart = this->currTrackTime;

		switch (this->direction) {
		case RangeIntervalMelody::Direction::UP:
			this->currentTendencyAmount = (rand() %
				(int)(this->upwardsTendencyLengthUpperLimit * quarterNoteMicroSeconds - this->upwardsTendencyLengthLowerLimit * quarterNoteMicroSeconds))
				+ (int)(this->upwardsTendencyLengthLowerLimit * quarterNoteMicroSeconds);
			break;
		case RangeIntervalMelody::Direction::DOWN:
			this->currentTendencyAmount = (rand() %
				(int)(this->downwardsTendencyLengthUpperLimit * quarterNoteMicroSeconds - this->downwardsTendencyLengthLowerLimit * quarterNoteMicroSeconds))
				+ (int)(this->downwardsTendencyLengthLowerLimit * quarterNoteMicroSeconds);
			break;
		case RangeIntervalMelody::Direction::SAME:
		default:
			this->currentTendencyAmount = (rand() %
				(int)(this->sameTendencyLengthUpperLimit * quarterNoteMicroSeconds - this->sameTendencyLengthLowerLimit * quarterNoteMicroSeconds))
				+ (int)(this->downwardsTendencyLengthLowerLimit * quarterNoteMicroSeconds);
			break;
		}
	}
}

void RangeIntervalMelody::setAmount() {
	int upperLimit, lowerLimit;
	TrackNote * previousNote = this->forTrack->getMostRecentNoteForUniqueNoteMelody("rrim" + this->uniqueKey)->getObject<TrackNote>();
	std::string melodyGroup = this->getParamDefault<std::string>(MelodyParameterType::MELODY_GROUP, "");
	std::vector<int> possibilities;

	switch (this->direction) {
	case RangeIntervalMelody::Direction::UP:
		upperLimit = this->upwardsTendencyAmountUpperLimit;
		if (upperLimit + previousNote->getNumber() > this->upperNoteLimit) {
			upperLimit = this->upperNoteLimit - previousNote->getNumber();
		}

		lowerLimit = this->upwardsTendencyAmountLowerLimit;
		if (lowerLimit + previousNote->getNumber()  > this->upperNoteLimit) {
			lowerLimit = this->upperNoteLimit - previousNote->getNumber();
		}

		for (int i = lowerLimit; i <= upperLimit; i++) {
			if (this->harmony->isHarmonicWithTime(previousNote->getNumber() + i, this->currTrackTime)) {
				possibilities.push_back(i);
			}
		}

		break;

	case RangeIntervalMelody::Direction::DOWN:
		upperLimit = this->downwardsTendencyAmountUpperLimit;
		if (previousNote->getNumber() - upperLimit < this->lowerNoteLimit) {
			upperLimit = previousNote->getNumber() - this->lowerNoteLimit;
		}
		lowerLimit = this->downwardsTendencyAmountLowerLimit;
		if (previousNote->getNumber() - lowerLimit < this->lowerNoteLimit) {
			lowerLimit = previousNote->getNumber() - this->lowerNoteLimit;
		}

		for (int i = lowerLimit; i <= upperLimit; i++) {
			if (this->harmony->isHarmonicWithTime(previousNote->getNumber() - i, this->currTrackTime)) {
				possibilities.push_back(i);
			}
		}

		break;

	case RangeIntervalMelody::Direction::SAME:
	default:
		if (this->harmony->isHarmonicWithTime(previousNote->getNumber(), this->currTrackTime)) {
			possibilities.push_back(0);
		}
	}

	if (possibilities.size() == 0) {
		this->forceNewDirection = true;
		directionTries.push_back(this->direction);
		if (directionTries.size() == 3) {
			this->amount = -1;
			this->directionTries.clear();
			return;
		} else {
			bool hasSame = false;
			bool hasDown = false;
			bool hasUp = false;

			for (RangeIntervalMelody::Direction direction : this->directionTries) {
				hasSame |= (direction == RangeIntervalMelody::Direction::SAME);
				hasDown |= (direction == RangeIntervalMelody::Direction::DOWN);
				hasUp |= (direction == RangeIntervalMelody::Direction::UP);
			}

			if (!hasSame) {
				this->direction = RangeIntervalMelody::Direction::SAME;
			}

			if (!hasUp) {
				this->direction = RangeIntervalMelody::Direction::UP;
			}

			if (!hasDown) {
				this->direction = RangeIntervalMelody::Direction::DOWN;
			}

			this->setAmount();
			this->directionTries.clear();
			return;
		}
	}

	this->amount = possibilities[rand() % possibilities.size()];
}

void RangeIntervalMelody::setRhythm(std::vector<float> rhythm) {
	this->rhythm = rhythm;
}


RangeIntervalMelody * RangeIntervalMelody::setHarmony(Harmony * harmony) {
	this->harmony = harmony;
	return this;
}

Harmony * RangeIntervalMelody::getHarmony() {
	return this->harmony;
}

bool RangeIntervalMelody::shouldHarmonizeWithTime() {
	return this->harmonyMode == RangeIntervalMelody::HarmonyMode::WITH_CURRENT_TIME;
}
