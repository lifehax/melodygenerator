#pragma once

#include <vector>
#include "SongGenerator.h"
#include "TrackBoard.h"

class Type;

class TwoMelodyChordRandomGenerator : public SongGenerator {
protected:
	TrackBoard * trackWork;
public:
	TwoMelodyChordRandomGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};