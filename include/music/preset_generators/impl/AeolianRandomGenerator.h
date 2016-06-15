#pragma once
#include <vector>

#include "SongGenerator.h"

class Type;

class AeolianRandomGenerator : public SongGenerator {
public:
	AeolianRandomGenerator(Type *, MIDITrack *);
	virtual void generateTrack();
};