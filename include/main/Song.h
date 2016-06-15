#pragma once

#include <boost/tuple/tuple.hpp>
#include "vector"

class Type;
class MIDITrack;

class Song {
private:
	MIDITrack * track;
	Type * type;
	int bpm;
	int microSecondsPerNote;

public:
	Song(Type * type);
	int getMicroSecondsPerNote();
	void setType(Type *);
	Type * getType();
	MIDITrack * makeTrack();
	void fillExtraOptions();
};
