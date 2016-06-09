#include "stdafx.h"

#include <boost/tuple/tuple.hpp>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>

#include "MultiInstrumentRandomGenerator.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"
#include "TrackBoard.h"
#include "ConnectedHarmonyMelody.h"
#include "NaturalMinorScale.h"
#include "DoubleHarmonicMinorScale.h"

MultiInstrumentRandomGenerator::MultiInstrumentRandomGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
	this->trackWork = new TrackBoard(target);
}

void MultiInstrumentRandomGenerator::generateTrack() {
	TrackBoardMelodyParams * trebleParams = this->trackWork->addDefaultParamType("treble");
	MelodyParameter<std::vector<std::string> *> * trebleModulatorParam = trebleParams->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
		new std::vector<std::string>({ "FunctionNoteModulation", "ScaleNoteModulation" })
		);
	MelodyParameter<int> * treblePriorityParam = trebleParams->setParam<int>(MelodyParameterType::PRIORITY, 3);

	MelodyParameter<ConnectedHarmonyMelody::HarmonyMode> * trebleHarmonyModeParam =
		trebleParams->setParam<ConnectedHarmonyMelody::HarmonyMode>(
			MelodyParameterType::HARMONY_MODE, ConnectedHarmonyMelody::HarmonyMode::BY_CALL);

	MelodyParameter<int> * trebleLowerNoteLimitParam = trebleParams->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 50);
	MelodyParameter<int> * trebleUpperNoteLimitParam = trebleParams->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 70);
	MelodyParameter<int64_t> * trebleTrackTimeParam = trebleParams->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
	MelodyParameter<int> * trebleNoteLengthParam = trebleParams->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	MelodyParameter<int> * trebleSizeParam = trebleParams->setParam<int>(MelodyParameterType::SIZE, 10);
	trebleParams->setParam<int>(MelodyParameterType::INSTRUMENT, std::stoi(this->type->getOptionValue("instrument3")));

	TrackBoardParamRandomize * trebleScaleParam = trebleParams->setRandomParam(MelodyParameterType::SCALE);
	MelodyParameter<Scale *> * trebleScaleParamOpt1 = trebleScaleParam->addParam<Scale *>(new DoubleHarmonicMinorScale(), 1);
	MelodyParameter<Scale *> * trebleScaleParamOpt2 = trebleScaleParam->addParam<Scale *>(new NaturalMinorScale(), 2);

	TrackBoardSubParam * trebleScaleModeParam = trebleParams->setSubParam(MelodyParameterType::SCALE_MODE, MelodyParameterType::SCALE);
	trebleScaleModeParam->addParam<std::string>(trebleScaleParamOpt1->getID(), "Eb");
	trebleScaleModeParam->addParam<std::string>(trebleScaleParamOpt2->getID(), "C");

	TrackBoardParamRandomize * trebleRootNoteParam = trebleParams->setRandomParam(MelodyParameterType::ROOT_NOTE);
	MelodyParameter<int> * trebleRootNoteParamOpt1 = trebleRootNoteParam->addParam<int>(64, 1);
	MelodyParameter<int> * trebleRootNoteParamOpt2 = trebleRootNoteParam->addParam<int>(58, 2);
	MelodyParameter<int> * trebleRootNoteParamOpt3 = trebleRootNoteParam->addParam<int>(54, 3);

	TrackBoardParamRandomize * trebleRhythmParam = trebleParams->setRandomParam(MelodyParameterType::RHYTHM);
	MelodyParameter<std::vector<float> *> * trebleRhythmParamOpt1 = trebleRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 1, 1, 1 }), 2);
	MelodyParameter<std::vector<float> *> * trebleRhythmParamOpt2 = trebleRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 1, 0.5, 0.25, 0.25, 1 }), 2);
	MelodyParameter<std::vector<float> *> * trebleRhythmParamOpt3 = trebleRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 0.25, 0.25, 1 }), 1);

	TrackBoardSubParam * trebleMelodyRepeatSizeParam = trebleParams->setSubParam(MelodyParameterType::MELODY_REPEAT_SIZE, MelodyParameterType::RHYTHM);
	trebleMelodyRepeatSizeParam->addParam<float>(trebleRhythmParamOpt1->getID(), 3);
	trebleMelodyRepeatSizeParam->addParam<float>(trebleRhythmParamOpt2->getID(), 3);
	trebleMelodyRepeatSizeParam->addParam<float>(trebleRhythmParamOpt3->getID(), 1.5);

	TrackBoardParamRandomize * trebleMelodyFunctionParam = trebleParams->setRandomParam(MelodyParameterType::MODULATION_FUNCTION);
	MelodyParameter<ModulatorFunction *> * trebleMelodyFunctionParamOpt1 = trebleMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearIncreaseMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * trebleMelodyFunctionParamOpt2 = trebleMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearDecreaseMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * trebleMelodyFunctionParamOpt3 = trebleMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::SinMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * trebleMelodyFunctionParamOpt4 = trebleMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpGainMelodyFunction, 2);
	MelodyParameter<ModulatorFunction *> * trebleMelodyFunctionParamOpt5 = trebleMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpLossMelodyFunction, 3);
	trebleParams->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "treble");





	TrackBoardMelodyParams * midParams = this->trackWork->addDefaultParamType("mid");
	MelodyParameter<std::vector<std::string> *> * midModulatorParam = midParams->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
		new std::vector<std::string>({ "FunctionNoteModulation", "ScaleNoteModulation" })
		);
	MelodyParameter<int> * midPriorityParam = midParams->setParam<int>(MelodyParameterType::PRIORITY, 1);

	MelodyParameter<ConnectedHarmonyMelody::HarmonyMode> * midHarmonyModeParam =
		midParams->setParam<ConnectedHarmonyMelody::HarmonyMode>(
			MelodyParameterType::HARMONY_MODE, ConnectedHarmonyMelody::HarmonyMode::BY_CALL);

	MelodyParameter<int> * midLowerNoteLimitParam = midParams->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 40);
	MelodyParameter<int> * midUpperNoteLimitParam = midParams->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 60);
	MelodyParameter<int64_t> * midTrackTimeParam = midParams->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
	MelodyParameter<int> * midNoteLengthParam = midParams->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	MelodyParameter<int> * midSizeParam = midParams->setParam<int>(MelodyParameterType::SIZE, 10);
	midParams->setParam<int>(MelodyParameterType::INSTRUMENT, std::stoi(this->type->getOptionValue("instrument2")));

	TrackBoardParamRandomize * midScaleParam = midParams->setRandomParam(MelodyParameterType::SCALE);
	MelodyParameter<Scale *> * midScaleParamOpt1 = midScaleParam->addParam<Scale *>(new DoubleHarmonicMinorScale(), 1);
	MelodyParameter<Scale *> * midScaleParamOpt2 = midScaleParam->addParam<Scale *>(new NaturalMinorScale(), 2);

	TrackBoardSubParam * midScaleModeParam = midParams->setSubParam(MelodyParameterType::SCALE_MODE, MelodyParameterType::SCALE);
	midScaleModeParam->addParam<std::string>(midScaleParamOpt1->getID(), "Eb");
	midScaleModeParam->addParam<std::string>(midScaleParamOpt2->getID(), "C");

	TrackBoardParamRandomize * midRootNoteParam = midParams->setRandomParam(MelodyParameterType::ROOT_NOTE);
	MelodyParameter<int> * midRootNoteParamOpt1 = midRootNoteParam->addParam<int>(48, 1);
	MelodyParameter<int> * midRootNoteParamOpt2 = midRootNoteParam->addParam<int>(52, 2);
	MelodyParameter<int> * midRootNoteParamOpt3 = midRootNoteParam->addParam<int>(44, 3);

	TrackBoardParamRandomize * midRhythmParam = midParams->setRandomParam(MelodyParameterType::RHYTHM);
	MelodyParameter<std::vector<float> *> * midRhythmParamOpt1 = midRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 1, 1, 1 }), 2);
	MelodyParameter<std::vector<float> *> * midRhythmParamOpt2 = midRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 1, 0.5, 0.5, 1 }), 2);
	MelodyParameter<std::vector<float> *> * midRhythmParamOpt3 = midRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 0.5, 1 }), 1);

	TrackBoardSubParam * midMelodyRepeatSizeParam = midParams->setSubParam(MelodyParameterType::MELODY_REPEAT_SIZE, MelodyParameterType::RHYTHM);
	midMelodyRepeatSizeParam->addParam<float>(midRhythmParamOpt1->getID(), 3);
	midMelodyRepeatSizeParam->addParam<float>(midRhythmParamOpt2->getID(), 3);
	midMelodyRepeatSizeParam->addParam<float>(midRhythmParamOpt3->getID(), 1.5);

	TrackBoardParamRandomize * midMelodyFunctionParam = midParams->setRandomParam(MelodyParameterType::MODULATION_FUNCTION);
	MelodyParameter<ModulatorFunction *> * midMelodyFunctionParamOpt1 = midMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearIncreaseMelodyFunction, 2);
	MelodyParameter<ModulatorFunction *> * midMelodyFunctionParamOpt2 = midMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearDecreaseMelodyFunction, 2);
	MelodyParameter<ModulatorFunction *> * midMelodyFunctionParamOpt3 = midMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::SinMelodyFunction, 3);
	MelodyParameter<ModulatorFunction *> * midMelodyFunctionParamOpt4 = midMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpGainMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * midMelodyFunctionParamOpt5 = midMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpLossMelodyFunction, 1);
	midParams->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "mid");



	TrackBoardMelodyParams * bassParams = this->trackWork->addDefaultParamType("bass");
	MelodyParameter<std::vector<std::string> *> * bassModulatorParam = bassParams->setParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR,
		new std::vector<std::string>({ "FunctionNoteModulation", "ScaleNoteModulation" })
		);
	MelodyParameter<int> * bassPriorityParam = bassParams->setParam<int>(MelodyParameterType::PRIORITY, 2);

	MelodyParameter<ConnectedHarmonyMelody::HarmonyMode> * bassHarmonyModeParam =
		bassParams->setParam<ConnectedHarmonyMelody::HarmonyMode>(
			MelodyParameterType::HARMONY_MODE, ConnectedHarmonyMelody::HarmonyMode::BY_CALL);

	MelodyParameter<int> * bassLowerNoteLimitParam = bassParams->setParam<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 15);
	MelodyParameter<int> * bassUpperNoteLimitParam = bassParams->setParam<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 35);
	MelodyParameter<int64_t> * bassTrackTimeParam = bassParams->setParam<int64_t>(MelodyParameterType::TRACK_TIME, 0);
	MelodyParameter<int> * bassNoteLengthParam = bassParams->setParam<int>(MelodyParameterType::NOTE_LENGTH, this->type->getMicroSecondsPerNote());
	MelodyParameter<int> * bassSizeParam = bassParams->setParam<int>(MelodyParameterType::SIZE, 4);
	bassParams->setParam<int>(MelodyParameterType::INSTRUMENT, std::stoi(this->type->getOptionValue("instrument1")));

	TrackBoardParamRandomize * bassScaleParam = bassParams->setRandomParam(MelodyParameterType::SCALE);
	MelodyParameter<Scale *> * bassScaleParamOpt1 = bassScaleParam->addParam<Scale *>(new DoubleHarmonicMinorScale(), 1);
	MelodyParameter<Scale *> * bassScaleParamOpt2 = bassScaleParam->addParam<Scale *>(new NaturalMinorScale(), 2);

	TrackBoardSubParam * bassScaleModeParam = bassParams->setSubParam(MelodyParameterType::SCALE_MODE, MelodyParameterType::SCALE);
	bassScaleModeParam->addParam<std::string>(bassScaleParamOpt1->getID(), "Eb");
	bassScaleModeParam->addParam<std::string>(bassScaleParamOpt2->getID(), "C");

	TrackBoardParamRandomize * bassRootNoteParam = bassParams->setRandomParam(MelodyParameterType::ROOT_NOTE);
	MelodyParameter<int> * bassRootNoteParamOpt1 = bassRootNoteParam->addParam<int>(25, 1);
	MelodyParameter<int> * bassRootNoteParamOpt2 = bassRootNoteParam->addParam<int>(30, 2);
	MelodyParameter<int> * bassRootNoteParamOpt3 = bassRootNoteParam->addParam<int>(34, 3);

	TrackBoardParamRandomize * bassRhythmParam = bassParams->setRandomParam(MelodyParameterType::RHYTHM);
	MelodyParameter<std::vector<float> *> * bassRhythmParamOpt1 = bassRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 1, 0.5, 0.5, 1 }), 2);
	MelodyParameter<std::vector<float> *> * bassRhythmParamOpt2 = bassRhythmParam->addParam<std::vector<float> *>(new std::vector<float>({ 2, 2, 1 }), 1);

	TrackBoardSubParam * bassMelodyRepeatSizeParam = bassParams->setSubParam(MelodyParameterType::MELODY_REPEAT_SIZE, MelodyParameterType::RHYTHM);
	bassMelodyRepeatSizeParam->addParam<float>(bassRhythmParamOpt1->getID(), 3);
	bassMelodyRepeatSizeParam->addParam<float>(bassRhythmParamOpt2->getID(), 5);

	TrackBoardParamRandomize * bassMelodyFunctionParam = bassParams->setRandomParam(MelodyParameterType::MODULATION_FUNCTION);
	MelodyParameter<ModulatorFunction *> * bassMelodyFunctionParamOpt1 = bassMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearIncreaseMelodyFunction, 2);
	MelodyParameter<ModulatorFunction *> * bassMelodyFunctionParamOpt2 = bassMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::LinearDecreaseMelodyFunction, 3);
	MelodyParameter<ModulatorFunction *> * bassMelodyFunctionParamOpt3 = bassMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::SinMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * bassMelodyFunctionParamOpt4 = bassMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpGainMelodyFunction, 1);
	MelodyParameter<ModulatorFunction *> * bassMelodyFunctionParamOpt5 = bassMelodyFunctionParam->addParam<ModulatorFunction *>(ModulatorFunctions::ExpLossMelodyFunction, 1);
	bassParams->setParam<std::string>(MelodyParameterType::MELODY_GROUP, "bass");


	TrackBoardMelody * trebleNotes = this->trackWork->addMelody("treble", "treble");
	TrackBoardMelody * midNotes = this->trackWork->addMelody("mid", "mid");
	TrackBoardMelody * bassNotes = this->trackWork->addMelody("bass", "bass");

	int64_t nextTreble = 0;
	int64_t nextMid = 0;
	int64_t nextBass = 0;
	int harmonizePriority = 4;

	ConnectedMelodies * connectedMelodies = new ConnectedMelodies();

	for (int64_t i = 0; i < type->getSongLength();) {
		ConnectedHarmonyMelody * treble, *mid, *bass;
		if (i == nextMid) {
			mid = midNotes->addMelody<ConnectedHarmonyMelody>();
			mid->setParam<int>(MelodyParameterType::PRIORITY, harmonizePriority++);
			mid->setConnections(connectedMelodies);
			mid->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);
			mid->addAsPhrase();
			nextMid = mid->getFinishTime();
		}

		if (i == nextBass) {
			bass = bassNotes->addMelody<ConnectedHarmonyMelody>();
			bass->setParam<int>(MelodyParameterType::PRIORITY, harmonizePriority++);
			bass->setConnections(connectedMelodies);
			bass->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);
			bass->addAsPhrase();
			nextBass = bass->getFinishTime();
		}

		if (i == nextTreble) {
			treble = trebleNotes->addMelody<ConnectedHarmonyMelody>();
			treble->setParam<int>(MelodyParameterType::PRIORITY, harmonizePriority++);
			treble->setConnections(connectedMelodies);
			treble->setParam<int64_t>(MelodyParameterType::TRACK_TIME, i);
			treble->addAsPhrase();
			nextTreble = treble->getFinishTime();
		}

		i = (std::min)({ nextTreble, nextMid, nextBass });
	}

	try {
		connectedMelodies->harmonize();
	} catch (std::exception const & ex) {
		throw ex;
	}
}
