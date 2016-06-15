#include "stdafx.h"

#include "PatternModulationMelodyType.h"
#include "PatternModulationMelodyGenerator.h"

PatternModulationMelodyType::PatternModulationMelodyType(int number, std::wstring name) : Type(number, name) {

}

int PatternModulationMelodyType::getBpm() {
	return 120;
}

int PatternModulationMelodyType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t PatternModulationMelodyType::getSongLength() {
	return 120000000;
}

SongGenerator * PatternModulationMelodyType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new PatternModulationMelodyGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * PatternModulationMelodyType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument", { "InstrumentList",{} } },
		{ "time_signature", { "TimeSignature",{} } }
	});
}
