#pragma once
#include <vector>

#include "SongGenerator.h"

class Type;

class PerfectFifthGenerator : public SongGenerator {
public:
	PerfectFifthGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};