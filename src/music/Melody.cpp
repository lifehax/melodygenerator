#include "stdafx.h"

#include <iostream>
#include <sstream>
#include "Melody.h"
#include "MIDITrack.h"

int Melody::NumberOfMelodies = 0;

Melody::Melody(MIDITrack * forTrack) {
	this->forTrack = forTrack;
	this->uniqueKey = "Melody" + std::to_string(Melody::NumberOfMelodies++);
}

MIDITrack * Melody::getTrack() {
	return this->forTrack;
}

std::string Melody::getUniqueName() {
	return this->uniqueKey;
}
