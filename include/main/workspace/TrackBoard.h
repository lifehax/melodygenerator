#pragma once

#include "Track.h"
#include "TrackBoardMelody.h"
#include "TrackBoardMelodyParams.h"
#include <map>
#include <string>

class TrackBoard {
protected:
	MIDITrack * forTrack;
	std::map<std::string, TrackBoardMelody *> * melodies;
	std::map<std::string, TrackBoardMelodyParams *> * melodyParamTypes;

public:
	TrackBoard(MIDITrack *);
	TrackBoardMelody * addMelody(std::string, std::string);
	TrackBoardMelodyParams * addDefaultParamType(std::string);
	MIDITrack * getTrack();
};
