#include "stdafx.h"

#include <stdlib.h>
#include <boost/tuple/tuple.hpp>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>

#include "RandomIntervalMelodyGenerator.h"
#include "Type.h"
#include "Note.h"
#include "MelodyParameter.h"
#include "Chord.h"

RandomIntervalMelodyGenerator::RandomIntervalMelodyGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
	this->midRangeMelody = new RangeIntervalMelody(this->target);
	this->midRangeMelody->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "midRange");
	this->midRangeMelody->setParam<int>(MelodyParameterType::ROOT_NOTE, 57);
	this->midRangeMelody->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	this->midRangeMelody->setUpwardsTendencyLengthRange(0.25, 3);
	this->midRangeMelody->setDownwardsTendencyLengthRange(0.25, 3);
	this->midRangeMelody->setSameTendencyLengthRange(0.25, 1);
	this->midRangeMelody->setUpwardsTendencyAmountRange(1, 7);
	this->midRangeMelody->setDownwardsTendencyAmountRange(1, 7);
	this->midRangeMelody->setNoteLimits(49, 62);
	this->midRangeMelody->setRhythm({ 1 });

	this->midRangeUpperMelody = new RangeIntervalMelody(this->target);
	this->midRangeUpperMelody->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "midRangeUpper");
	this->midRangeUpperMelody->setParam<int>(MelodyParameterType::ROOT_NOTE, 64);
	this->midRangeUpperMelody->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	this->midRangeUpperMelody->setUpwardsTendencyLengthRange(0.25, 3);
	this->midRangeUpperMelody->setDownwardsTendencyLengthRange(0.25, 3);
	this->midRangeUpperMelody->setSameTendencyLengthRange(0.25, 1);
	this->midRangeUpperMelody->setUpwardsTendencyAmountRange(1, 12);
	this->midRangeUpperMelody->setDownwardsTendencyAmountRange(1, 12);
	this->midRangeUpperMelody->setNoteLimits(57, 75);
	this->midRangeUpperMelody->setRhythm({ 0.5, 0.5, 0.25, 0.25, 0.25 });

	this->midRangeLowerMelody = new RangeIntervalMelody(this->target);
	this->midRangeLowerMelody->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "midRangeLower");
	this->midRangeLowerMelody->setParam<int>(MelodyParameterType::ROOT_NOTE, 33);
	this->midRangeLowerMelody->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	this->midRangeLowerMelody->setUpwardsTendencyLengthRange(0.25, 3);
	this->midRangeLowerMelody->setDownwardsTendencyLengthRange(0.25, 3);
	this->midRangeLowerMelody->setSameTendencyLengthRange(0.25, 1);
	this->midRangeLowerMelody->setUpwardsTendencyAmountRange(1, 12);
	this->midRangeLowerMelody->setDownwardsTendencyAmountRange(1, 12);
	this->midRangeLowerMelody->setNoteLimits(33, 57);
	this->midRangeLowerMelody->setRhythm({ 1, 1, 0.5 });

	this->bassMelody = new RangeIntervalMelody(this->target);
	this->bassMelody->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "bass");
	this->bassMelody->setParam<int>(MelodyParameterType::ROOT_NOTE, 21);
	this->bassMelody->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	this->bassMelody->setUpwardsTendencyLengthRange(0.25, 3);
	this->bassMelody->setDownwardsTendencyLengthRange(0.25, 3);
	this->bassMelody->setSameTendencyLengthRange(0.25, 1);
	this->bassMelody->setUpwardsTendencyAmountRange(1, 12);
	this->bassMelody->setDownwardsTendencyAmountRange(1, 12);
	this->bassMelody->setNoteLimits(21, 34);
	this->bassMelody->setRhythm({ 2, 1, 2 });
}

void RandomIntervalMelodyGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));
	int currTrackTime = 0;
	bool showNotes = false;
	int64_t readyAtTime;
	srand((unsigned int)time(NULL));

	for (int64_t trackTick = 0; trackTick <= this->type->getSongLength();) {
		this->midRangeMelody->addMelodyAtTime(trackTick);
		this->midRangeUpperMelody->addMelodyAtTime(trackTick);
		this->midRangeLowerMelody->addMelodyAtTime(trackTick);
		this->bassMelody->addMelodyAtTime(trackTick);

		readyAtTime = this->midRangeMelody->readyAtTime();

		if (this->midRangeUpperMelody->readyAtTime() < readyAtTime && this->midRangeUpperMelody->readyAtTime() > trackTick) {
			readyAtTime = this->midRangeUpperMelody->readyAtTime();
		}

		if (this->midRangeLowerMelody->readyAtTime() < readyAtTime && this->midRangeLowerMelody->readyAtTime() > trackTick) {
			readyAtTime = this->midRangeLowerMelody->readyAtTime();
		}

		if (this->bassMelody->readyAtTime() < readyAtTime && this->bassMelody->readyAtTime() > trackTick) {
			readyAtTime = this->bassMelody->readyAtTime();
		}

		trackTick = readyAtTime;
	}
}