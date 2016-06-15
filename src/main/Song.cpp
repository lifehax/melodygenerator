#include "stdafx.h"

#include <iostream>

#include "Track.h"
#include "Song.h"
#include "Type.h"
#include "SongGenerator.h"
#include "Note.h"
#include "TrackNote.h"

Song::Song(Type * type) {
	this->track = new MIDITrack();
	this->setType(type);
}

void Song::setType(Type * type) {
	this->type = type;
	this->bpm = type->getBpm();
	this->microSecondsPerNote = this->type->getMicroSecondsPerNote();
}

Type * Song::getType() {
	return this->type;
}

int Song::getMicroSecondsPerNote() {
	return this->microSecondsPerNote;
}

void Song::fillExtraOptions() {
	return;
}

MIDITrack * Song::makeTrack() {
	this->track->setTempo(bpm);
	this->type->getGenerator(this->track)->generateTrack();
	return this->track;
}
