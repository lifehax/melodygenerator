#include "stdafx.h"

#include "WideRandomIntervalMelodyType.h"
#include "WideRandomIntervalMelodyGenerator.h"

WideRandomIntervalMelodyType::WideRandomIntervalMelodyType(int number, std::wstring name) : Type(number, name) {

}

int WideRandomIntervalMelodyType::getBpm() {
	return 120;
}

int WideRandomIntervalMelodyType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t WideRandomIntervalMelodyType::getSongLength() {
	return 120000000;
}

SongGenerator * WideRandomIntervalMelodyType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new WideRandomIntervalMelodyGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * WideRandomIntervalMelodyType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } }
	});
}
