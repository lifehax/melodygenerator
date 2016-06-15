#include "stdafx.h"
#include "Generator.h"
#include "Song.h"
#include "Type.h"

void Generator::generate(int type) {
	Type * songType = Type::Create(type);
	songType->setOptionValues(this->optionValues);
	Song * song = new Song(songType);
	song->makeTrack();
}

void Generator::setOptionValues(std::map<std::string, std::string> * optionValues) {
	this->optionValues = optionValues;
}
