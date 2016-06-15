#include "stdafx.h"

#include "NoteByNoteMelody.h"

NoteByNoteMelody::NoteByNoteMelody(MIDITrack * forTrack) : Melody(forTrack) {

}

bool NoteByNoteMelody::isReadyForNote(int64_t trackTime) {
	return trackTime >= this->waitForNoteBegin + this->waitForNoteTime;
}

void NoteByNoteMelody::waitForNextNote(int64_t trackTime, int length) {
	this->waitForNoteBegin = trackTime;
	this->waitForNoteTime = length;
}

int64_t NoteByNoteMelody::readyAtTime() {
	return this->waitForNoteBegin + this->waitForNoteTime;
}
