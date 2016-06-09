#pragma once

#include "TrackBoardMelodyType.h"
#include "MelodyParameter.h"
#include <map>
#include <vector>

class Melody;
class TrackBoard;
class PhraseMelody;
class TrackBoardMelodyParams;
class ConnectedHarmonyMelody;

class TrackBoardMelody {
protected: 
	TrackBoard * board;
	TrackBoardMelodyParams * params;

	std::vector<Melody *> melodies;

public:
	TrackBoardMelody(TrackBoard * board, TrackBoardMelodyParams * params);

	template<typename MelodyType>
	MelodyType * addMelody() {
		MelodyType * melody = TrackBoardMelodyType<MelodyType>::Create(this->board->getTrack());
		this->params->addToMelody(melody, NULL);
		this->melodies.push_back(melody);
		return melody;
	}

	template<typename MelodyType>
	MelodyType * addMelody(std::map<MelodyParameterType, std::string> * variations) {
		MelodyType * melody = TrackBoardMelodyType<MelodyType>::Create(this->board->getTrack());
		this->params->addToMelody(melody, variations);
		this->melodies.push_back(melody);
		return melody;
	}
};
