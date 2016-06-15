#include "stdafx.h"
#include "Type.h"
#include "Max108RandomType.h"
#include "AeolianRandomType.h"
#include "PerfectFifthType.h"
#include "RandomIntervalMelodyType.h"
#include "WideRandomIntervalMelodyType.h"
#include "PatternModulationMelodyType.h"
#include "TwoMelodySingleNoteRandomType.h"
#include "TwoMelodyChordRandomType.h"
#include "MultiInstrumentRandomType.h"

const std::vector<std::wstring>  Type::list = {
	L"Max 108 Random",
	L"Natural Minor Random",
	L"Perfect Fifth",
	L"Random Interval Melody",
	L"Wide Random Interval Melody",
	L"Pattern Modulation Melody",
	L"Two Melody Single Note Random",
	L"Two Melody Chord Random",
	L"Multi Instrument Random"
};

std::map<std::wstring, Type *(*)(int, std::wstring)> Type::classMap({
	{ L"Max 108 Random", &createTypeFactory<Max108RandomType> },
	{ L"Natural Minor Random", &createTypeFactory<AeolianRandomType> },
	{ L"Perfect Fifth", &createTypeFactory<PerfectFifthType> },
	{ L"Random Interval Melody", &createTypeFactory<RandomIntervalMelodyType> },
	{ L"Wide Random Interval Melody", &createTypeFactory<WideRandomIntervalMelodyType> },
	{ L"Pattern Modulation Melody", &createTypeFactory<PatternModulationMelodyType> },
	{ L"Two Melody Single Note Random", &createTypeFactory<TwoMelodySingleNoteRandomType> },
	{ L"Two Melody Chord Random", &createTypeFactory<TwoMelodyChordRandomType> },
	{ L"Multi Instrument Random", &createTypeFactory<MultiInstrumentRandomType> }
});

Type::Type(int number, std::wstring name) {
	this->number = number;
	this->name = name;
	this->optionValues = new std::map<std::string, std::string>();
}

Type * Type::CreateFromName(std::wstring name) {
	 auto findVal = std::find(Type::list.begin(), Type::list.end(), name);
	 if (findVal == Type::list.end()) {
		 return NULL;
	 }
	 return Type::classMap[name](findVal - Type::list.begin(), name);
}

Type * Type::Create(int number) {
	return Type::classMap[Type::list[number]](number, Type::list[number]);
}

std::wstring Type::getName() {
	return this->name;
}

int Type::getTickResolution() {
	return 1000;
}

std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * Type::getOptions() {
	return NULL;
}

void Type::setOptionValues(std::map<std::string, std::string> * optionValues) {
	this->optionValues = optionValues;
}

std::string Type::getOptionValue(std::string option) {
	return this->optionValues->at(option);
}