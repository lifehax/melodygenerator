#include "stdafx.h"

#include "MultiInstrumentRandomType.h"
#include "MultiInstrumentRandomGenerator.h"

MultiInstrumentRandomType::MultiInstrumentRandomType(int number, std::wstring name) : Type(number, name) {

}

int MultiInstrumentRandomType::getBpm() {
	return 120;
}

int MultiInstrumentRandomType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t MultiInstrumentRandomType::getSongLength() {
	return 120000000;
}

SongGenerator * MultiInstrumentRandomType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new MultiInstrumentRandomGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * MultiInstrumentRandomType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument1", { "InstrumentList", { { "label", "Bass Instrument" } } } },
		{ "instrument2", { "InstrumentList", { { "label", "Mid Instrument" } } } },
		{ "instrument3", { "InstrumentList", { { "label", "Treble Instrument" } } } }
	});
}
