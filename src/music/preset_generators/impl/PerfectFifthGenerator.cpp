#include "stdafx.h"

#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <functional>

#include "PerfectFifthGenerator.h"
#include "Type.h"
#include "Note.h"
#include "Chord.h"

PerfectFifthGenerator::PerfectFifthGenerator(Type * type, MIDITrack * target) : SongGenerator(type, target) {
}

void PerfectFifthGenerator::generateTrack() {
	this->target->setDefaultInstrument(std::stoi(this->type->getOptionValue("instrument")));
	srand((unsigned int)time(NULL));

	for (int beatPosition = 0; beatPosition < this->type->getSongLength(); beatPosition++) {
		int startNumber = rand() % 15;

		std::vector<int> * thisFifthNotes = new std::vector<int>();
		for (int noteNumber = 0; noteNumber < 15; noteNumber++) {
			int thisNote = noteNumber + startNumber;
			if (thisNote >= 15) {
				thisNote -= 15;
			}
			bool isInHarmony = true;
			for (int otherNote : *thisFifthNotes) {
				int noteDistance = std::abs(otherNote - thisNote) % 12;
				isInHarmony &= ((noteDistance == 7) || (noteDistance == 4) || (noteDistance == 0) || (noteDistance == 9));
			}
			if (isInHarmony) {
				this->target->addItem(TrackItem::CreateNote(beatPosition * this->type->getMicroSecondsPerNote(), thisNote, this->type->getMicroSecondsPerNote()));
				thisFifthNotes->push_back(thisNote);
			}
		}
	}
}