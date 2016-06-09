#include "stdafx.h"

#include "SongGenerator.h"
#include "Type.h"
#include "TrackNote.h"

SongGenerator::SongGenerator(Type * type, MIDITrack * target) {
	this->target = target;
	this->type = type;
}