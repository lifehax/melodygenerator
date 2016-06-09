#include "stdafx.h"

#include "PerfectFifthType.h"
#include "PerfectFifthGenerator.h"

PerfectFifthType::PerfectFifthType(int number, std::wstring name) : Type(number, name) {

}

int PerfectFifthType::getBpm() {
	return 120;
}

int PerfectFifthType::getMicroSecondsPerNote() {
	return 60000000 / 120;
}

int64_t PerfectFifthType::getSongLength() {
	return 480;
}

SongGenerator * PerfectFifthType::getGenerator(MIDITrack * target) {
	return (SongGenerator *)new PerfectFifthGenerator(this, target);
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * PerfectFifthType::getOptions() {
	return new std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>>({
		{ "instrument",{ "InstrumentList",{} } }
	});
}
