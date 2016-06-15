#include "stdafx.h"
#include <sstream>
#include <iomanip>
#include "TimeSignatureOption.h"
#include "MIDI.h"

TimeSignatureOption::TimeSignatureOption(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) : ComboBoxOption(options, subOptionsMap) {
}

std::map<std::string, std::string> * TimeSignatureOption::getOptions() {
	std::map<std::string, std::string> * options = new std::map<std::string, std::string>();
	options->insert_or_assign("4/4", "4/4");
	options->insert_or_assign("3/4", "3/4");
	options->insert_or_assign("2/4", "2/4");
	options->insert_or_assign("3/8", "3/8");
	options->insert_or_assign("6/8", "6/8");
	options->insert_or_assign("9/8", "9/8");
	options->insert_or_assign("5/4", "5/4");
	options->insert_or_assign("7/8", "7/8");
	options->insert_or_assign("3/10", "3/10");
	options->insert_or_assign("5/24", "5/24");
	options->insert_or_assign("2.5/4", "2.5/4");
	return options;
}

std::wstring TimeSignatureOption::getLabel() {
	return L"Time Signature:";
}

std::string TimeSignatureOption::getType() {
	return "Time Signature";
}
