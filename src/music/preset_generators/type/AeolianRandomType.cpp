#include "stdafx.h"

#include "AeolianRandomType.h"
#include "AeolianRandomGenerator.h"

AeolianRandomType::AeolianRandomType(int number, std::wstring name) : Type(number, name) {

}

int AeolianRandomType::getBpm() {
	return 120;
}

int AeolianRandomType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t AeolianRandomType::getSongLength() {
	return 480;
}

SongGenerator * AeolianRandomType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new AeolianRandomGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * AeolianRandomType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } }
	});
}
