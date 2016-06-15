#pragma once

#include <vector>
#include "SongGenerator.h"
#include "TrackBoard.h"

class Type;

class PatternModulationMelodyGenerator : public SongGenerator {
protected:
	TrackBoard * trackWork;
public:
	PatternModulationMelodyGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};