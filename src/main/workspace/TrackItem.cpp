#include "stdafx.h"

#include "TrackItem.h"
#include "TrackNote.h"
#include "TrackChord.h"
#include "TrackItemObject.h"

TrackItem::TrackItem(TrackItemObject * object) {
	this->object = object;
}

std::vector<TrackNote *> * TrackItem::getAllNotes() {
	if (this->isChord()) {
		return this->getObject<TrackChord>()->getNotes();
	} else {
		return new std::vector<TrackNote *>({ this->getObject<TrackNote>() });
	}
}

void TrackItem::setMetaInformation(std::string name, std::string value) {
	this->object->setMetaInformation(name, value);
}

std::map<std::string, std::string> * TrackItem::getMetaInformation() {
	return this->object->getMetaInformation();
}

bool TrackItem::isForMelody(std::string name) {
	return this->object->isForMelody(name);
}

void TrackItem::addMelody(std::string name) {
	this->object->addMelody(name);
}

std::vector<std::string> * TrackItem::getMelodies() {
	return this->object->getMelodies();
}

void TrackItem::setMelodyGroup(std::string noteMelodyGroup) {
	this->object->setMelodyGroup(noteMelodyGroup);
}

std::string TrackItem::getMelodyGroup() {
	return this->object->getMelodyGroup();
}

int64_t TrackItem::getTrackTime() {
	return this->object->getTrackTime();
}

void TrackItem::setTrackTime(int64_t trackTime) {
	this->object->setTrackTime(trackTime);
}

void TrackItem::setInstrument(int instrument) {
	this->object->setInstrument(instrument);
}

int TrackItem::getInstrument() {
	return this->object->getInstrument();
}

void TrackItem::setLength(int length) {
	this->object->setLength(length);
}

int TrackItem::getLength() {
	return this->object->getLength();
}

bool TrackItem::isType(TrackItemType type) {
	return this->object->isType(type);
}

bool TrackItem::isNote() {
	return this->object->isNote();
}

bool TrackItem::isChord() {
	return this->object->isChord();
}

void TrackItem::setNoteByNumber(int note) {
	this->object->setNoteByNumber(note);
}

int TrackItem::getNumber() {
	return this->object->getNumber();
}

void TrackItem::switchToNote() {
	if (!this->isNote()) {
		TrackNote * note = new TrackNote(this->getTrackTime(), this->getNumber(), this->getLength());
		note->setInstrument(this->getInstrument());
		note->setMelodyGroup(this->getMelodyGroup());
		this->object = note;
	}
}

void TrackItem::switchToChord(std::string degree) {
	if (this->isChord()) {
		((TrackChord *)object)->setDegree(degree);
	} else {
		TrackChord * chord = new TrackChord(this->getTrackTime(), this->getNumber(), degree, this->getLength());
		chord->setMelodyGroup(this->getMelodyGroup());
		chord->setInstrument(this->getInstrument());
		this->object = chord;
	}
}

TrackItem * TrackItem::CreateNote(int64_t time, int note, int length) {
	TrackNote * noteObj = new TrackNote(time, note, length);
	return new TrackItem(noteObj);
}

TrackItem * TrackItem::CreateChord(int64_t time, int note, int length, std::string degree) {
	TrackChord * chord = new TrackChord(time, note, degree, length);
	return new TrackItem(chord);
}

bool TrackItem::HasTimeOverlap(TrackItem * a, TrackItem * b) {
	return a->getTrackTime() + a->getLength() >= b->getTrackTime() && b->getTrackTime() + b->getLength() >= a->getTrackTime();
}
