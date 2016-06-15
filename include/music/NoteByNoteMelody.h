#pragma once

#include "Melody.h"

class NoteByNoteMelody : public Melody {
protected:
	int64_t currTrackTime;

	int waitForNoteTime;
	int64_t waitForNoteBegin;
public:
	NoteByNoteMelody(MIDITrack *);

	virtual void addMelodyAtTime(int64_t trackTime) = 0;

	bool isReadyForNote(int64_t trackTime);
	void waitForNextNote(int64_t trackTime, int length);
	int64_t readyAtTime();
};
