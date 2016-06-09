#include "stdafx.h"

#include "TwoMelodyChordRandomType.h"
#include "TwoMelodyChordRandomGenerator.h"

TwoMelodyChordRandomType::TwoMelodyChordRandomType(int number, std::wstring name) : Type(number, name) {

}

int TwoMelodyChordRandomType::getBpm() {
	return 120;
}

int TwoMelodyChordRandomType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t TwoMelodyChordRandomType::getSongLength() {
	return 120000000;
}

SongGenerator * TwoMelodyChordRandomType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new TwoMelodyChordRandomGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * TwoMelodyChordRandomType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } },
		{ "time_signature",{ "TimeSignature",{} } }
	});
}
