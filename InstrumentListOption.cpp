#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include "InstrumentListOption.h"
#include "MIDI.h"

InstrumentListOption::InstrumentListOption(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) : ComboBoxOption(options, subOptionsMap) {
}

std::map<std::string, std::string> * InstrumentListOption::getOptions() {
	std::map<std::string, std::string> * options = new std::map<std::string, std::string>();
	for (auto instrument : MIDI::instruments) {
		std::ostringstream ss;
		ss << std::setw(8) << std::setfill('0') << instrument.first;
		options->insert_or_assign(ss.str(), instrument.second);
	}
	return options;
}

std::wstring InstrumentListOption::getLabel() {
	auto search = this->subOptionsMap.find("label");
	if (search != this->subOptionsMap.end()) {
		return GetWC((*search).second.c_str());
	} else {
		return L"Instrument:";
	}
}

std::string InstrumentListOption::getType() {
	return "Instrument List";
}
