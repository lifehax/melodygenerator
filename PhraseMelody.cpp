#include "stdafx.h"
#include "PhraseMelody.h"

PhraseMelody::PhraseMelody(MIDITrack * forTrack) : Melody(forTrack) {
}

int PhraseMelody::getPhraseLength() {
	int phraseLength = 0;
	int numNotes = this->getParam<int>(MelodyParameterType::SIZE);
	int noteLength = this->getParam<int>(MelodyParameterType::NOTE_LENGTH);
	std::vector<float> * rhythm = this->getParam<std::vector<float> *>(MelodyParameterType::RHYTHM);

	for (int note = 0; note < numNotes; note++) {
		phraseLength += (int)(noteLength * (*rhythm)[note % rhythm->size()]);
	}

	return phraseLength;
}

int PhraseMelody::getMelodyRepeatLength() {
	float numNotes = this->getParam<float>(MelodyParameterType::MELODY_REPEAT_SIZE);
	int noteLength = this->getParam<int>(MelodyParameterType::NOTE_LENGTH);

	return (int)(numNotes * noteLength);
}

int64_t PhraseMelody::getFinishTime() {
	int64_t trackPositionForMelody = this->getParam<int64_t>(MelodyParameterType::TRACK_TIME);
	return trackPositionForMelody + this->getPhraseLength();
}
