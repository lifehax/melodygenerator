#include "stdafx.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>

#include "Max108RandomGenerator.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"

Max108RandomGenerator::Max108RandomGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
}

void Max108RandomGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));
	srand((unsigned int)time(NULL));
	std::vector<int> * harmonyTypes = new std::vector<int>({ 0, 3, 4, 5, 7, 8, 9 });

	for (int beatPosition = 0; beatPosition < this->type->getSongLength(); beatPosition++) {

		std::vector<int> * thisHarmonyNotes = new std::vector<int>();
		bool notesLeftToProcess = true;
		bool thisPassSucceeded = false;
		do {
			thisPassSucceeded = false;
			int startNumber = rand() % 108;
			int direction = rand() % 2 == 1 ? 1 : -1;

			for (int noteNumber = direction==1?0:108; (direction == 1 && noteNumber < 108) || (direction == -1 && noteNumber > 0); noteNumber += direction) {
				int thisNote = noteNumber + startNumber;
				if (thisNote >= 108) {
					thisNote -= 108;
				}

				bool thisNoteHasHarmony = true;
				for (int otherNote : *thisHarmonyNotes) {
					bool hasAHarmony = false;
					for(int harmony: *harmonyTypes) {
						if (thisNote != otherNote) {
							int noteDistance = std::abs(thisNote - otherNote) % 12;
							hasAHarmony |= (noteDistance == harmony);
						}
						if (hasAHarmony) break;
					}
					thisNoteHasHarmony &= hasAHarmony;
				}

				if (thisNoteHasHarmony) {
					thisPassSucceeded = true;
					thisHarmonyNotes->push_back(thisNote);
					this->target->addItem(TrackItem::CreateNote(beatPosition * this->type->getMicroSecondsPerNote(), thisNote, this->type->getMicroSecondsPerNote()));
					break;
				}
			}
		} while (thisPassSucceeded);
	}
}