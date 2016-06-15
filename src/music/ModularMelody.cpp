#include "stdafx.h"

#include <vector>

#include "ModularMelody.h"
#include "MIDITrack.h"
#include "NoteModulation.h"
#include "MelodyParameter.h"

const std::vector<std::string> ModularMelody::list = {
	"FunctionNoteModulation",
	"ScaleNoteModulation",
	"PatternNoteModulation",
	"RandomNoteModulation",
	"RandomShiftNoteModulation",
	"ChordNoteModulation"
};

std::map<std::string, NoteModulation *(*)(ModularMelody *)> ModularMelody::classMap({
	{ "FunctionNoteModulation", &createModulationFactory<FunctionNoteModulation> },
	{ "ScaleNoteModulation", &createModulationFactory<ScaleNoteModulation> },
	{ "PatternNoteModulation", &createModulationFactory<PatternNoteModulation> },
	{ "RandomNoteModulation", &createModulationFactory<RandomNoteModulation> },
	{ "RandomShiftNoteModulation", &createModulationFactory<RandomShiftNoteModulation> },
	{ "ChordNoteModulation", &createModulationFactory<ChordNoteModulation> }
});

ModularMelody::ModularMelody(MIDITrack * forTrack) : PhraseMelody(forTrack) {
	this->modulators = new std::vector<NoteModulation *>();
}

void ModularMelody::addAsPhrase() {
	std::vector<std::string> * modulatorList = this->getParam<std::vector<std::string> *>(MelodyParameterType::MODULATOR);

	for (auto modulator : *modulatorList) {
		this->modulators->push_back(ModularMelody::classMap[modulator](this));
	}

	int rootNote = this->getParam<int>(MelodyParameterType::ROOT_NOTE);
	int phraseSize = this->getParam<int>(MelodyParameterType::SIZE);
	int noteLength = this->getParam<int>(MelodyParameterType::NOTE_LENGTH);
	int instrument = this->getParamDefault<int>(MelodyParameterType::INSTRUMENT, -1);
	int64_t trackTime = this->getParam<int64_t>(MelodyParameterType::TRACK_TIME);
	int upperLimit = this->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);
	std::vector<float> * rhythm = this->getParam<std::vector<float> *>(MelodyParameterType::RHYTHM);
	std::string melodyGroup = this->getParamDefault<std::string>(MelodyParameterType::MELODY_GROUP, "");

	std::vector<TrackItem *> * phraseNotes = new std::vector<TrackItem *>();

	int64_t currTime = trackTime;
	for (int i = 0; i < phraseSize; i++) {
		int thisNoteLength = (int)(noteLength * (*rhythm)[i % rhythm->size()]);
		TrackItem * newNote = TrackItem::CreateNote(currTime, rootNote, thisNoteLength);
		newNote->setMelodyGroup(melodyGroup);
		newNote->addMelody(this->getUniqueName());
		newNote->setInstrument(instrument);
		phraseNotes->push_back(newNote);
		currTime += thisNoteLength;
	}

	for (auto modulator : *modulators) {
		modulator->modifyNotes(phraseNotes);
	}

	for (auto trackNote : *phraseNotes) {
		if (trackNote->getNumber() < lowerLimit) {
			trackNote->setNoteByNumber(lowerLimit);
		}
		if (trackNote->getNumber() > upperLimit) {
			trackNote->setNoteByNumber(upperLimit);
		}
		this->forTrack->addItem(trackNote);
	}
}