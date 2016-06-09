#include "stdafx.h"

#include "RandomIntervalMelodyType.h"
#include "RandomIntervalMelodyGenerator.h"

RandomIntervalMelodyType::RandomIntervalMelodyType(int number, std::wstring name) : Type(number, name) {

}

int RandomIntervalMelodyType::getBpm() {
	return 120;
}

int RandomIntervalMelodyType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t RandomIntervalMelodyType::getSongLength() {
	return 120000000;
}

SongGenerator * RandomIntervalMelodyType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new RandomIntervalMelodyGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * RandomIntervalMelodyType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } }
	});
}
