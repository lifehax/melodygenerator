#pragma once

#include <vector>
#include "SongGenerator.h"
#include "TrackBoard.h"

class Type;

class MultiInstrumentRandomGenerator : public SongGenerator {
protected:
	TrackBoard * trackWork;
public:
	MultiInstrumentRandomGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};