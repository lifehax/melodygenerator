#include "stdafx.h"

#include "Max108RandomType.h"
#include "Max108RandomGenerator.h"

Max108RandomType::Max108RandomType(int number, std::wstring name) : Type(number, name) {
	
}

int Max108RandomType::getBpm() {
	return 240;
}

int Max108RandomType::getMicroSecondsPerNote() {
	return 60000000 / 240;
}

int64_t Max108RandomType::getSongLength() {
	return 480;
}

SongGenerator * Max108RandomType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new Max108RandomGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * Max108RandomType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } }
	});
}
