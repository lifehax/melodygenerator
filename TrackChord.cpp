#include "stdafx.h"

#include "Chord.h"
#include "TrackItem.h"
#include "TrackNote.h"
#include "TrackChord.h"

TrackChord::TrackChord(int64_t time, int root, std::string degree, int length) : TrackItemObject(time, length, TrackItemType::CHORD) {
	this->degree = degree;
	this->root = root;
	this->notes = new std::vector<boost::tuple<TrackNote *, bool, int>>();
}

void TrackChord::setNotes() {
	std::vector<std::pair<int, bool>> * chordNotes = Chord::GetChord(this->degree, this->root);
	this->removeAllNotes();
	int rootNoteNum = -1;
	for (auto chordNote: *chordNotes) {
		if (chordNote.second) {
			rootNoteNum = chordNote.first;
		}
	}
	if (rootNoteNum == -1) {
		throw new GeneratorException("No root note returned from chord class.");
	}
	for (auto chordNote : *chordNotes) {
		this->notes->push_back({
			new TrackNote(this->getTrackTime(), chordNote.first, this->getLength()),
			chordNote.second,
			chordNote.first - rootNoteNum
		});
	}
}

void TrackChord::removeAllNotes() {
	this->notes->clear();
}

std::vector<TrackNote *> * TrackChord::getNotes() {
	std::vector<TrackNote *> * notes = new std::vector<TrackNote *>();
	for (auto chord : *(this->notes)) {
		notes->push_back(chord.get<0>());
	}
	return notes;
}

std::string TrackChord::getDegree() {
	return this->degree;
}

void TrackChord::setDegree(std::string degree) {
	this->degree = degree;
	this->setNotes();
}

int TrackChord::getRootNote() {
	return this->root;
}

void TrackChord::setRootNote(int rootNote) {
	this->root = rootNote;
	this->setNotes();
}

int TrackChord::getNumber() {
	return this->root;
}

void TrackChord::setNoteByNumber(int rootNote) {
	this->setRootNote(rootNote);
}

