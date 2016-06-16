#include "stdafx.h"

#include "TrackItemObject.h"

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
