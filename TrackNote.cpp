#include "stdafx.h"

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "TrackNote.h"
#include "Note.h"
#include "Chord.h"

TrackNote::TrackNote(int64_t time, int note, int length) : TrackItemObject(time, length, TrackItemType::NOTE) {
	this->setNoteByNumber(note);
}

std::string TrackNote::getNote() {
	return note;
}

void TrackNote::setNote(std::string note) {
	this->note = note;
	this->number = Note::idxMap.at(note);
}

void TrackNote::setNoteByNumber(int noteNumber) {
	this->number = noteNumber;
	this->note = Note::notes[noteNumber].first;
	this->freq = Note::notes[noteNumber].second;
}

int TrackNote::getNumber() {
	return this->number;
}

int TrackNote::getDB() {
	return db;
}

void TrackNote::setDB(int db) {
	this->db = db;
}

void TrackNote::setFreq(double freq) {
	this->freq = freq;
}

double TrackNote::getFreq() {
	return freq;
}

bool TrackNote::equals(TrackNote * compareTo) {
	return getNote() == compareTo->getNote() && getLength() == compareTo->getLength();
}