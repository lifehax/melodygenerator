#include "stdafx.h"

#include <boost/algorithm/string.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>
#include <numeric>

#include "PatternModulationMelodyGenerator.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"
#include "TrackBoard.h"
#include "RandomRhythmGenerator.h"
#include "RandomPatternGenerator.h"
#include "ConnectedHarmonyMelody.h"

PatternModulationMelodyGenerator::PatternModulationMelodyGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
	this->trackWork = new TrackBoard(target);
}

void PatternModulationMelodyGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));

	std::string timeSignature = this->type->getOptionValue("time_signature");
	std::vector<std::string> splitTimeSignature;
	boost::split(splitTimeSignature, timeSignature, boost::is_any_of("/"));
	this->target->setBeatsPerBar(std::stod(splitTimeSignature[0]));
	this->target->setNoteDivision(std::stoi(splitTimeSignature[1]));

	int numMelodyTypes = (rand() % 4) + 2;
	std::vector<std::string> melodyTypeNames;
	std::map<std::string, TrackBoardMelody *> melodyTypeMap;
	std::map<std::string, int64_t> * melodyEndPos = new std::map<std::string, int64_t>();
	RandomRhythmGenerator * rhythmGenerator = new RandomRhythmGenerator(this->target->getBeatsPerBar(), this->target->getNoteDivision());
	RandomPatternGenerator * patternGenerator = new RandomPatternGenerator();
	int priorityLevel = 0;

	for (int melody = 0; melody < numMelodyTypes; melody++) {
		std::string melodyTypeName = "melodyType" + melody;

		melodyTypeNames.push_back(melodyTypeName);
		TrackBoardMelodyParams * params = this->trackWork->addDefaultParamType(melodyTypeName);

		MelodyParameter<std::vector<std::string> *> * modulatorParam = params->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
			new std::vector<std::string>({ "PatternNoteModulation" })
		);

		int noteRange = (rand() % 15) + 12;
		int lower = (rand() % (70 - noteRange)) + 20;

		MelodyParameter<int> * lowerNoteLimitParam = params->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, lower);
		MelodyParameter<int> * upperNoteLimitParam = params->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, lower+noteRange);
		params->setParam<std::string>(MelodyParameterType::MELODY_GROUP, melodyTypeName);

		MelodyParameter<int64_t> * trackTimeParam = params->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
		MelodyParameter<int> * noteLengthParam = params->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());

		int melodyNoteLength = rand() % 20 + 5;
		MelodyParameter<int> * sizeParam = params->setParam<int>(MelodyParameterType::SIZE, melodyNoteLength);

		int rootNote = (rand() % noteRange) + lower;
		if (rootNote > 107) {
			rootNote = 107;
		}
		MelodyParameter<int> * rootNoteParam = params->setParam<int>(MelodyParameterType::ROOT_NOTE, rootNote);

		std::vector<float> * rhythm = rhythmGenerator->getRhythm();
		MelodyParameter<std::vector<float> *> * rhythmParam = params->setParam<std::vector<float> *>(MelodyParameterType::RHYTHM, rhythm);
		MelodyParameter<float> * melodyRepeatSizeParam = params->setParam<float>(MelodyParameterType::MELODY_REPEAT_SIZE, std::accumulate(rhythm->begin(), rhythm->end(), 0.0f));

		std::vector<int> * pattern = patternGenerator->getPattern();
		MelodyParameter<std::vector<int> *> * patternParam = params->setParam<std::vector<int> *>(MelodyParameterType::MODULATION_PATTERN, pattern);

		melodyTypeMap.insert_or_assign(
			melodyTypeName,
			this->trackWork->addMelody(melodyTypeName, melodyTypeName)
		);

		melodyEndPos->insert_or_assign(
			melodyTypeName,
			0
		);
	}
	
	ConnectedMelodies * connectedMelodies = new ConnectedMelodies();

	for (int64_t i = 0; i < type->getSongLength();) {
		for(auto melody: melodyTypeNames) {
			if (i == melodyEndPos->at(melody)) {
				ConnectedHarmonyMelody * newMelody = melodyTypeMap[melody]->addMelody<ConnectedHarmonyMelody>();

				newMelody->setParam<int>(MelodyParameterType::PRIORITY, priorityLevel++);
				newMelody->setConnections(connectedMelodies);
				newMelody->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);

				int lowerNoteLimit = newMelody->getParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT);
				int upperNoteLimit = newMelody->getParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT);

				int rootNote = (rand() % (upperNoteLimit - lowerNoteLimit)) + lowerNoteLimit;
				newMelody->setParam<int>(MelodyParameterType::ROOT_NOTE, rootNote);

				newMelody->addAsPhrase();
				melodyEndPos->insert_or_assign(melody, newMelody->getFinishTime());
			}
		}


		i = (std::min_element)(melodyEndPos->begin(), melodyEndPos->end(), [](std::pair<std::string, int64_t> a, std::pair<std::string, int64_t> b) -> bool {
			return a.second < b.second;
		})->second;
	}
}
