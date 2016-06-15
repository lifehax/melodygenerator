#include "stdafx.h"

#include "TrackBoard.h"
#include "TrackBoardMelody.h"

TrackBoard::TrackBoard(MIDITrack * forTrack) {
	this->forTrack = forTrack;
	this->melodies = new std::map<std::string, TrackBoardMelody *>();
	this->melodyParamTypes = new std::map<std::string, TrackBoardMelodyParams *>();
}

TrackBoardMelody * TrackBoard::addMelody(std::string name, std::string paramType) {
	TrackBoardMelody * trackBoardMelody = new TrackBoardMelody(this, this->melodyParamTypes->at(paramType));
	this->melodies->insert_or_assign(name, trackBoardMelody);
	return trackBoardMelody;
}

TrackBoardMelodyParams * TrackBoard::addDefaultParamType(std::string paramType) {
	TrackBoardMelodyParams * params = new TrackBoardMelodyParams(this);
	this->melodyParamTypes->insert_or_assign(paramType, params);
	return params;
}

MIDITrack * TrackBoard::getTrack() {
	return this->forTrack;
}

