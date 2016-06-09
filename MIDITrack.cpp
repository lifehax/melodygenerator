#include "stdafx.h"
#include "MIDITrack.h"


#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <boost/filesystem.hpp>

#include "Track.h"
#include "MIDI.h"
#include "TrackNote.h"

MIDITrack::MIDITrack() : Track() {
	this->notesMap = new std::map<int64_t, std::vector<TrackItem *> *>();
	this->defaultInstrument = 1;
	this->noteDivision = 4;
	this->beatsPerBar = 4;
}


void MIDITrack::setDefaultInstrument(int instrument) {
	this->defaultInstrument = instrument;
}

int MIDITrack::getDefaultInstrument() {
	return this->defaultInstrument;
}


void MIDITrack::setBeatsPerBar(double beatsPerBar) {
	this->beatsPerBar = beatsPerBar;
}

double MIDITrack::getBeatsPerBar() {
	return this->beatsPerBar;
}

void MIDITrack::setNoteDivision(int noteDivision) {
	this->noteDivision = noteDivision;
}

int MIDITrack::getNoteDivision() {
	return this->noteDivision;
}

std::wstring MIDITrack::getFileName(std::wstring name) {
	if (boost::filesystem::exists(name + L"NotesTable.html")) {
		int i = 0;
		do {
			i++;
		} while (boost::filesystem::exists(name + std::to_wstring(i) + L"NotesTable.html"));
		name = name + std::to_wstring(i);
	}
	return name;
}

void MIDITrack::saveInfoHtml(std::wstring name) {
	if (boost::filesystem::exists(name + L"NotesTable.html")) {
		int i = 0;
		do {
			i++;
		} while (boost::filesystem::exists(name + std::to_wstring(i) + L"NotesTable.html"));
		name = name + std::to_wstring(i) + L"NotesTable.html";
	}
	else {
		name = name + L"NotesTable.html";
	}

	std::ofstream htmlFile;
	htmlFile.open(name);

	htmlFile << "<html><head><title>Musical Notes Meta Information</title></head><body>";
	htmlFile << "<table border=\"1\">";
	htmlFile << "<tr><th>Track Time</th><th>Notes</th></tr>";
	for (auto it = notesMap->begin(); it != notesMap->end(); ++it) {
		htmlFile << "<tr><td>" << it->first << "</td>";
		std::vector<TrackItem *> * noteList = it->second;
		//std::sort(noteList->begin(), noteList->end(), TrackItem::SortByNumber);

		htmlFile << "<td><table border=\"1\">";
		for (auto nit = noteList->begin(); nit != noteList->end(); ++nit) {
			TrackItem * checkNote = *nit;
			for (auto thisNote : *(checkNote->getAllNotes())) {
				htmlFile << "<tr><th align=\"left\">Note:</th><th align=\"left\">Frequency:</th><th align=\"left\">Length:</th></tr>";
				htmlFile << "<tr><td>" << thisNote->getNote() << "</td><td>" << thisNote->getFreq() << "</td><td>" << thisNote->getLength() << "</td></tr>";
				htmlFile << "<tr><th colspan=\"3\" align=\"left\">Melodies:</th></tr><tr><td colspan=\"3\">" << thisNote->getMelodyGroup();
				htmlFile << "</td></tr>";
				for (auto metaRow : *(thisNote->getMetaInformation())) {
					htmlFile << "<tr><th colspan=\"3\" align=\"left\">" << metaRow.first << ":</th></tr><tr><td colspan=\"3\">";
					htmlFile << metaRow.second;
					htmlFile << "</td></tr>";
				}
			}
		}
		htmlFile << "</table></td></tr>";
	}
	htmlFile << "</table>";
	htmlFile << "</body></html>";
}

void MIDITrack::removeItem(TrackItem * toRemove) {
	auto notesAtPos = notesMap->find(toRemove->getTrackTime());
	if (notesAtPos != notesMap->end()) {
		std::vector<TrackItem *> * notes = notesAtPos->second;
		for (auto noteIt = notes->begin(); noteIt != notes->end(); noteIt++) {
			if (*noteIt == toRemove) {
				notes->erase(noteIt);
				return;
			}
		}
	}
}

void MIDITrack::addItem(TrackItem * toAdd) {
	if (notesMap->find(toAdd->getTrackTime()) == notesMap->end()) {
		notesMap->insert_or_assign(toAdd->getTrackTime(), new std::vector<TrackItem *>());
	}
	if (toAdd->getInstrument() == -1) {
		toAdd->setInstrument(this->getDefaultInstrument());
	}
	notesMap->at(toAdd->getTrackTime())->push_back(toAdd);
}

void MIDITrack::addItems(std::vector<TrackItem *> * toAdd) {
	for (auto note : *toAdd) {
		this->addItem(note);
	}
}

std::map<int64_t, std::vector<TrackItem *> *> * MIDITrack::getTrackMap() {
	return notesMap;
}

void MIDITrack::saveMIDI(std::wstring fileName) {
	MIDI midiHandler(this, fileName);
	midiHandler.save();
}

void MIDITrack::setTempo(int tempo) {
	this->tempo = tempo;
}

int MIDITrack::getTempo() {
	return tempo;
}

int64_t MIDITrack::size() {
	std::vector<TrackItem *> * mostRecent = this->getMostRecentNotes();
	if (mostRecent->size() == 0) {
		return 0;
	}
	else {
		return mostRecent->at(0)->getTrackTime();
	}
}

int64_t MIDITrack::sizeForMelody(std::string melodyName) {
	std::vector<TrackItem *> * mostRecent = this->getMostRecentNotesForMelody(melodyName);
	if (mostRecent->size() == 0) {
		return 0;
	}
	else {
		return mostRecent->at(0)->getTrackTime();
	}
}

std::vector<TrackItem *> * MIDITrack::getMostRecentNotes() {
	std::vector<TrackItem *> * recent = new std::vector<TrackItem *>();
	auto last = this->notesMap->rbegin();
	if (last != this->notesMap->rend()) {
		recent = last->second;
	}
	return recent;
}

std::vector<TrackItem *> * MIDITrack::getMostRecentNotesForMelody(std::string melodyName) {
	std::vector<TrackItem *> * recent = new std::vector<TrackItem *>();
	auto last = this->notesMap->rbegin();
	while (last != this->notesMap->rend() && recent->size() == 0) {
		for (auto it : *last->second) {
			if (it->isForMelody(melodyName)) {
				recent->push_back(it);
			}
		}
		++last;
	}
	return recent;
}

TrackItem * MIDITrack::getMostRecentNoteForUniqueNoteMelody(std::string melodyName) {
	std::vector<TrackItem *> * recent = getMostRecentNotesForMelody(melodyName);
	return recent->size() > 0 ? recent->at(0) : NULL;
}

std::vector<TrackItem *> * MIDITrack::getNotesAtTime(int64_t time) {
	std::vector<TrackItem *> * atTime = new std::vector<TrackItem *>();
	for (auto trackPos : *notesMap) {
		if (time >= trackPos.first) {
			for (auto it : *trackPos.second) {
				if (time < it->getTrackTime() + it->getLength()) {
					atTime->push_back(it);
				}
			}
		}
	}
	return atTime;
}

std::vector<TrackItem *> * MIDITrack::getNotesAtTimeForMelody(int64_t time, std::string melodyName) {
	std::vector<TrackItem *> * atTime = new std::vector<TrackItem *>();
	for (auto trackPos : *notesMap) {
		if (time >= trackPos.first) {
			for (auto it : *trackPos.second) {
				if (time < it->getTrackTime() + it->getLength()) {
					if (it->isForMelody(melodyName)) {
						atTime->push_back(it);
					}
				}
			}
		}
	}
	return atTime;
}
std::vector<TrackItem *> * MIDITrack::getNotesAtTimeForMelodies(int64_t time, std::vector<std::string> * melodies) {
	std::vector<TrackItem *> * atTime = new std::vector<TrackItem *>();
	for (auto trackPos : *notesMap) {
		if (time >= trackPos.first) {
			for (auto it : *trackPos.second) {
				if (time < it->getTrackTime() + it->getLength()) {
					for (std::string melodyName : *melodies) {
						if (it->isForMelody(melodyName)) {
							atTime->push_back(it);
							break;
						}
					}
				}
			}
		}
	}
	return atTime;
}

std::vector<TrackItem *> * MIDITrack::getAllNotesForMelody(std::string melody) {
	std::vector<TrackItem *> * forMelody = new std::vector<TrackItem *>();
	for (auto trackPos : *notesMap) {
		for (auto it : *trackPos.second) {
			if (it->isForMelody(melody)) {
				forMelody->push_back(it);
				break;
			}
		}
	}
	return forMelody;
}

std::vector<TrackItem *> * MIDITrack::getAllNotesForMelodyGroup(std::string melody) {
	std::vector<TrackItem *> * forMelody = new std::vector<TrackItem *>();
	for (auto trackPos : *notesMap) {
		for (auto it : *trackPos.second) {
			if (it->getMelodyGroup() == melody) {
				forMelody->push_back(it);
				break;
			}
		}
	}
	return forMelody;
}
