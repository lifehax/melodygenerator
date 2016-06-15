#include "stdafx.h"

#include "TrackItem.h"
#include "TrackNote.h"
#include "TrackChord.h"

TrackItemObject::TrackItemObject(int64_t trackTime, int length, TrackItemType type) {
	this->length = length;
	this->type = type;
	this->melodyGroup = "";
	this->melodies = new std::vector<std::string>();
	this->metaInformation = new std::map<std::string, std::string>();
	this->trackTime = trackTime;
	this->midiInstrument = -1;
}

void TrackItemObject::setMetaInformation(std::string name, std::string value) {
	this->metaInformation->insert_or_assign(name, value);
}

std::map<std::string, std::string> * TrackItemObject::getMetaInformation() {
	return this->metaInformation;
}

bool TrackItemObject::isForMelody(std::string name) {
	return std::find(this->melodies->begin(), this->melodies->end(), name) != this->melodies->end();
}

void TrackItemObject::addMelody(std::string name) {
	this->melodies->push_back(name);
}

std::vector<std::string> * TrackItemObject::getMelodies() {
	return this->melodies;
}

void TrackItemObject::setMelodyGroup(std::string noteMelodyGroup) {
	this->melodyGroup = noteMelodyGroup;
}

std::string TrackItemObject::getMelodyGroup() {
	return this->melodyGroup;
}

int64_t TrackItemObject::getTrackTime() {
	return trackTime;
}

void TrackItemObject::setTrackTime(int64_t trackTime) {
	this->trackTime = trackTime;
}

void TrackItemObject::setInstrument(int instrument) {
	this->midiInstrument = instrument;
}

int TrackItemObject::getInstrument() {
	return this->midiInstrument;
}

void TrackItemObject::setLength(int length) {
	this->length = length;
}

int TrackItemObject::getLength() {
	return length;
}

bool TrackItemObject::isType(TrackItemType type) {
	return this->type == type;
}

bool TrackItemObject::isNote() {
	return this->isType(TrackItemType::NOTE) || this->isType(TrackItemType::HARMONOUS_NOTE);
}

bool TrackItemObject::isChord() {
	return this->isType(TrackItemType::CHORD);
}

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
		int instrument = this->getInstrument();
		this->object = new TrackNote(this->getTrackTime(), this->getNumber(), this->getLength());
		this->object->setInstrument(instrument);
	}
}

void TrackItem::switchToChord(std::string degree) {
	if (this->isChord()) {
		((TrackChord *)object)->setDegree(degree);
	} else {
		int instrument = this->getInstrument();
		this->object = new TrackChord(this->getTrackTime(), this->getNumber(), degree, this->getLength());
		this->object->setInstrument(instrument);
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
