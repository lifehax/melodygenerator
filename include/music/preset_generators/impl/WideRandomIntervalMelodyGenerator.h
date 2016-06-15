#pragma once

#include <vector>
#include "SongGenerator.h"
#include "TrackBoard.h"

class Type;

class WideRandomIntervalMelodyGenerator : public SongGenerator {
protected:
	TrackBoard * trackWork;
public:
	WideRandomIntervalMelodyGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};