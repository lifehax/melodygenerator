#pragma once

#include <vector>
#include "SongGenerator.h"
#include "TrackBoard.h"

class Type;

class TwoMelodySingleNoteRandomGenerator : public SongGenerator {
protected:
	TrackBoard * trackWork;
public:
	TwoMelodySingleNoteRandomGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};