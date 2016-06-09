#pragma once

#include "MIDI.h"
#include "MIDITrack.h"
#include "TrackNote.h"
#include "vector"

class Type;

class SongGenerator {
protected:
	Type * type;
	MIDITrack * target;
public:
	SongGenerator(Type *, MIDITrack *);
	virtual void generateTrack()=0;
};