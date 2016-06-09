#include "stdafx.h"

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "FunctionNoteModulation.h"

FunctionNoteModulation::FunctionNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
	this->withFunction = melody->getParam<ModulatorFunction *>(MelodyParameterType::MODULATION_FUNCTION);
}

void FunctionNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	int64_t trackPositionForMelody = this->forMelody->getParam<int64_t>(MelodyParameterType::TRACK_TIME);
	int upperLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::UPPER_NOTE_LIMIT, 107);
	int lowerLimit = this->forMelody->getParamDefault<int>(MelodyParameterType::LOWER_NOTE_LIMIT, 0);

	for(auto note: *phraseNotes) {
		int phrasePosition = (int)(note->getTrackTime() - trackPositionForMelody);
		int newCloseness = (*(this->withFunction))(this->forMelody, phraseNotes, phrasePosition, note->getTrackTime());
		if (newCloseness > upperLimit) {
			newCloseness = upperLimit;
		} else if (newCloseness < lowerLimit) {
			newCloseness = lowerLimit;
		}
		note->setNoteByNumber(newCloseness);
	}
}
