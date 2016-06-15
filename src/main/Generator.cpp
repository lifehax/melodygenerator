#include "stdafx.h"
#include "Generator.h"
#include "Song.h"
#include "Type.h"
#include "MIDITrack.h"

void Generator::generate(int type) {
	Type * songType = Type::Create(type);
	songType->setOptionValues(this->optionValues);
	Song * song = new Song(songType);
	MIDITrack * madeTrack = song->makeTrack();
	madeTrack->saveMIDI(songType->getName());
	
}

void Generator::setOptionValues(std::map<std::string, std::string> * optionValues) {
	this->optionValues = optionValues;
}
