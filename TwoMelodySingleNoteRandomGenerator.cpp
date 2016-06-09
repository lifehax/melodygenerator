#include "stdafx.h"

#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

#include "TwoMelodySingleNoteRandomGenerator.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"
#include "TrackBoard.h"
#include "ConnectedHarmonyMelody.h"
#include "NaturalMinorScale.h"
#include "DoubleHarmonicMinorScale.h"
#include "WeightRandomRhythmGenerator.h"

TwoMelodySingleNoteRandomGenerator::TwoMelodySingleNoteRandomGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
	this->trackWork = new TrackBoard(target);
}

void TwoMelodySingleNoteRandomGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));

	std::string timeSignature = this->type->getOptionValue("time_signature");
	std::vector<std::string> splitTimeSignature;
	boost::split(splitTimeSignature, timeSignature, boost::is_any_of("/"));
	this->target->setBeatsPerBar(std::stod(splitTimeSignature[0]));
	this->target->setNoteDivision(std::stoi(splitTimeSignature[1]));

	WeightRandomRhythmGenerator * bassRhythmGenerator = new WeightRandomRhythmGenerator(this->target->getBeatsPerBar(), this->target->getNoteDivision());
	bassRhythmGenerator->setWeightMap({
		{ 1.0f, 4 },
		{ 2.0f, 3 },
		{ 4.0f, 1 }
	});


	TrackBoardMelodyParams * bassParams = this->trackWork->addDefaultParamType("bass");
	MelodyParameter<std::vector<std::string> *> * bassModulatorParam = bassParams->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
		new std::vector<std::string>({ "RandomShiftNoteModulation" })
		);

	int bassLowLow = 20;
	int bassLowHigh = 30;
	int bassHighLow = 35;
	int bassHighHigh = 45;

	int bassLow = (rand() % (bassLowHigh - bassLowLow)) + bassLowLow;
	int bassHigh = (rand() % (bassHighHigh - bassHighLow)) + bassHighLow;
	if (bassHigh - bassLow < 12) {
		bassHigh = bassLow + 12;
	}

	MelodyParameter<int> * bassLowerNoteLimitParam = bassParams->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, bassLow);
	MelodyParameter<int> * bassUpperNoteLimitParam = bassParams->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, bassHigh);
	MelodyParameter<int64_t> * bassTrackTimeParam = bassParams->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
	MelodyParameter<int> * bassNoteLengthParam = bassParams->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());

	bassParams->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "bass");

	int bassNote = (rand() % ((bassHigh - 5) - (bassLow + 5))) + bassLow;
	MelodyParameter<int> * bassRootNoteParam = bassParams->setParam<int>(MelodyParameterType::ROOT_NOTE, bassNote);

	std::vector<float> * bassRhythm = bassRhythmGenerator->getRhythm();
	MelodyParameter<std::vector<float> *> * bassRhythmParam = bassParams->setParam<std::vector<float> *>(MelodyParameterType::RHYTHM, bassRhythm);

	WeightRandomRhythmGenerator * midRhythmGenerator = new WeightRandomRhythmGenerator(this->target->getBeatsPerBar(), this->target->getNoteDivision());
	midRhythmGenerator->setWeightMap({
		{0.25f, 1},
		{0.5f, 2},
		{1.0f, 2},
		{2.0f, 1}
	});

	TrackBoardMelodyParams * midParams = this->trackWork->addDefaultParamType("mid");
	MelodyParameter<std::vector<std::string> *> * midModulatorParam = midParams->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
		new std::vector<std::string>({ "RandomShiftNoteModulation" })
	);

	int midLowLow = 35;
	int midLowHigh = 45;
	int midHighLow = 60;
	int midHighHigh = 80;

	int midLow = (rand() % (midLowHigh - midLowLow)) + midLowLow;
	int midHigh = (rand() % (midHighHigh - midHighLow)) + midHighLow;
	if (midHigh - midLow < 12) {
		midHigh = midLow + 12;
	}

	MelodyParameter<int> * midLowerNoteLimitParam = midParams->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, midLow);
	MelodyParameter<int> * midUpperNoteLimitParam = midParams->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, midHigh);

	MelodyParameter<int64_t> * midTrackTimeParam = midParams->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
	MelodyParameter<int> * midNoteLengthParam = midParams->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());

	midParams->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "mid");

	int midNote = (rand() % ((midHigh-5) - (midLow+5))) + midLow;
	MelodyParameter<int> * midRootNoteParam = midParams->setParam<int>(MelodyParameterType::ROOT_NOTE, midNote);

	std::vector<float> * rhythm = midRhythmGenerator->getRhythm();
	MelodyParameter<std::vector<float> *> * midRhythmParam = midParams->setParam<std::vector<float> *>(MelodyParameterType::RHYTHM, rhythm);


	TrackBoardMelody * midNotes = this->trackWork->addMelody("mid", "mid");
	TrackBoardMelody * bassNotes = this->trackWork->addMelody("bass", "bass");

	int64_t nextMid = 0;
	int64_t nextBass = 0;
	int harmonizePriority = 0;
	int nextBassRhythm = rand() % 4 + 1;
	int nextMidRhythm = rand() % 4 + 1;
	if (nextMidRhythm > 2) nextMidRhythm = 1;

	ConnectedMelodies * connectedMelodies = new ConnectedMelodies();

	for (int64_t i = 0; i < type->getSongLength();) {
		ConnectedHarmonyMelody *mid, *bass;

		if (i == nextBass) {
			int pick = ((rand() % 5) + 1);
			if (pick > 3) pick = 1;
			int thisNote = (rand() % ((bassHigh - 5) - (bassLow + 5))) + bassLow;
			bass = bassNotes->addMelody<ConnectedHarmonyMelody>();
			bass->setParam<int>(MelodyParameterType::PRIORITY, harmonizePriority++);
			bass->setParam<int>(MelodyParameterType::SIZE, pick * bassRhythm->size());
			bass->setParam<int>(MelodyParameterType::ROOT_NOTE, thisNote);

			if (nextBassRhythm = 0) {
				std::vector<float> * bassRhythm = bassRhythmGenerator->getRhythm();
				bass->setParam<std::vector<float> *>(MelodyParameterType::RHYTHM, bassRhythm);
				nextBassRhythm = rand() % 4 + 1;
			} else {
				nextBassRhythm--;
			}

			bass->setConnections(connectedMelodies);
			bass->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);
			bass->addAsPhrase();
			nextBass = bass->getFinishTime();
		}

		if (i == nextMid) {
			int pick = ((rand() % 5) + 1);
			if (pick > 3) pick = 1;
			int thisNote = (rand() % ((midHigh - 5) - (midLow + 5))) + midLow;
			mid = midNotes->addMelody<ConnectedHarmonyMelody>();
			mid->setParam<int>(MelodyParameterType::PRIORITY, harmonizePriority++);
			mid->setParam<int>(MelodyParameterType::SIZE, pick * rhythm->size());
			mid->setParam<int>(MelodyParameterType::ROOT_NOTE, thisNote);

			if (nextMidRhythm = 0) {
				std::vector<float> * midRhythm = midRhythmGenerator->getRhythm();
				mid->setParam<std::vector<float> *>(MelodyParameterType::RHYTHM, midRhythm);
				nextMidRhythm = rand() % 4 + 1;
				if (nextMidRhythm > 2) nextMidRhythm = 1;
			} else {
				nextMidRhythm--;
			}

			mid->setConnections(connectedMelodies);
			mid->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);
			mid->addAsPhrase();
			nextMid = mid->getFinishTime();
		}

		i = (std::min)({ nextMid, nextBass });
	}
}
