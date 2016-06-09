#include "stdafx.h"

#include "TwoMelodySingleNoteRandomType.h"
#include "TwoMelodySingleNoteRandomGenerator.h"

TwoMelodySingleNoteRandomType::TwoMelodySingleNoteRandomType(int number, std::wstring name) : Type(number, name) {

}

int TwoMelodySingleNoteRandomType::getBpm() {
	return 120;
}

int TwoMelodySingleNoteRandomType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t TwoMelodySingleNoteRandomType::getSongLength() {
	return 120000000;
}

SongGenerator * TwoMelodySingleNoteRandomType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new TwoMelodySingleNoteRandomGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * TwoMelodySingleNoteRandomType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument", {"InstrumentList", {}}},
		{ "time_signature",{ "TimeSignature",{} } }
	});
}
