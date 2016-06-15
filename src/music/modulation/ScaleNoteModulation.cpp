#include "stdafx.h"

#include "Track.h"
#include "Scale.h"
#include "ModularMelody.h"
#include "ScaleNoteModulation.h"

ScaleNoteModulation::ScaleNoteModulation(ModularMelody * melody) : NoteModulation(melody) {
	this->withScale = melody->getParam<Scale *>(MelodyParameterType::SCALE);
}

void ScaleNoteModulation::modifyNotes(std::vector<TrackItem *> * phraseNotes) {
	std::string mode = this->forMelody->getParam<std::string>(MelodyParameterType::SCALE_MODE);
	int64_t trackPositionForMelody = this->forMelody->getParam<int64_t>(MelodyParameterType::TRACK_TIME);

	std::vector<int> * scaleNotes = this->withScale->getModeNotes(mode);
	for (auto note : *phraseNotes) {
		int noteDistance = -1;
		int closestNote;
		for (int scaleNote : *scaleNotes) {
			if ((noteDistance == -1 || std::abs(scaleNote - note->getNumber()) <= noteDistance)) {
				noteDistance = std::abs(scaleNote - note->getNumber());
				closestNote = scaleNote;
			}
		}
		note->setMetaInformation("Scale", this->withScale->getName() + " in " + mode);
		note->setNoteByNumber(closestNote);
	}
}
