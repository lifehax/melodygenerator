#pragma once
#include <vector>

#include "SongGenerator.h"

class Type;

class Max108RandomGenerator : public SongGenerator {
public:
	Max108RandomGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};