#include "stdafx.h"

#include <map>
#include <vector>
#include "ModulatorFunctions.h"
#include "ModularMelody.h"
#include "MelodyParameter.h"
#include "TrackItem.h"
#include "TrackNote.h"

ModulatorFunction * ModulatorFunctions::ExpGainMelodyFunction = new ModulatorFunction([](
	ModularMelody * forMelody, std::vector<TrackItem *> * phraseNotes, int position, int64_t trackTime
) -> int {
	int upperLimit = forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int rootNote = forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);

	int phraseLength = forMelody->getMelodyRepeatLength();

	double coefficient = (double)(upperLimit - rootNote) / (double)pow(phraseLength, 2);

	int result = (int)(coefficient * (double)pow((position % phraseLength), 2)) + rootNote;

	return result;
});

ModulatorFunction * ModulatorFunctions::ExpLossMelodyFunction = new ModulatorFunction([](
	ModularMelody * forMelody, std::vector<TrackItem *> * phraseNotes, int position, int64_t trackTime
) -> int {
	int lowLimit = forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	int rootNote = forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);

	int phraseLength = forMelody->getMelodyRepeatLength();

	double coefficient = (double)(lowLimit - rootNote) / (double)pow(phraseLength, 2);

	int result = (int)(coefficient * (double)pow((position % phraseLength), 2)) + rootNote;
	return result;
});

ModulatorFunction * ModulatorFunctions::LinearIncreaseMelodyFunction = new ModulatorFunction([](
	ModularMelody * forMelody, std::vector<TrackItem *> * phraseNotes, int position, int64_t trackTime
) -> int {
	int upperLimit = forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int rootNote = forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);

	int phraseLength = forMelody->getMelodyRepeatLength();

	double coefficient = (double)(upperLimit - rootNote) / (double)phraseLength;

	int result = (int)(coefficient * (position % phraseLength)) + rootNote;
	return result;
});

ModulatorFunction * ModulatorFunctions::LinearDecreaseMelodyFunction = new ModulatorFunction([](
	ModularMelody * forMelody, std::vector<TrackItem *> * phraseNotes, int position, int64_t trackTime
) -> int {
	int lowLimit = forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	int rootNote = forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);

	int phraseLength = forMelody->getMelodyRepeatLength();

	double coefficient = (double)(lowLimit - rootNote) / (double)phraseLength;

	int result = (int)(coefficient * (position % phraseLength)) + rootNote;
	return result;
});

ModulatorFunction * ModulatorFunctions::SinMelodyFunction = new ModulatorFunction([](
	ModularMelody * forMelody, std::vector<TrackItem *> * phraseNotes, int position, int64_t trackTime
) -> int {
	int lowLimit = forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	int upperLimit = forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int rootNote = forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);

	int phraseLength = forMelody->getMelodyRepeatLength();
	double amplitude = (upperLimit - lowLimit) / 2;


	int result = (int)((amplitude * sin((2.0 *  PI * (double)position) / (double)phraseLength)
		+ asin(((double)rootNote - ((double)lowLimit + amplitude)) / amplitude)) + ((double)lowLimit + (double)amplitude));
	return result;
});
