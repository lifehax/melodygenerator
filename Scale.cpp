#include "stdafx.h"

#include <vector>

#include "Scale.h"
#include "Note.h"

std::vector<int> * Scale::getNotes(int startNote) {
	std::vector<int> * intervals = this->getIntervals();
	std::vector<int> * notes = new std::vector<int>();
	for(int interval: *intervals) {
		notes->push_back(startNote + interval);
	}
	return notes;
}

std::vector<int> * Scale::getAllNotes() {
	std::vector<int> * allNotes = new std::vector<int>();
	std::vector<std::string> * modes = this->getModes();
	std::vector<int> * intervals = this->getIntervals();
	for (std::string mode : *modes) {
		for (int notesForMode : Note::typeNums.at(mode)) {
			for (int interval : *intervals) {
				if (std::find(allNotes->begin(), allNotes->end(), notesForMode + interval) == allNotes->end()) {
					allNotes->push_back(notesForMode + interval);
				}
			}
		}
	}
	return allNotes;
}

bool Scale::isValidNoteInScale(int note) {
	std::vector<std::string> * modes = this->getModes();
	std::vector<int> * intervals = this->getIntervals();
	bool hasNote = false;
	for (std::string mode : *modes) {
		for (int number : Note::typeNums.at(mode)) {
			for (int interval : *intervals) {
				if ((interval + number) == note) {
					hasNote = true;
					break;
				}
			}
		}
		if (hasNote) break;
	}
	return hasNote;
}

std::vector<int> *  Scale::getModeNotes(std::string mode) {
	std::vector<int> * allNotes = new std::vector<int>();
	std::vector<int> * intervals = this->getIntervals();
	for (int notesForMode : Note::typeNums.at(mode)) {
		for (int interval : *intervals) {
			if (std::find(allNotes->begin(), allNotes->end(), notesForMode + interval) == allNotes->end()) {
				allNotes->push_back(notesForMode + interval);
			}
		}
	}

	return allNotes;
}

bool Scale::isValidNoteInScaleMode(int note, std::string mode) {
	std::vector<int> * intervals = this->getIntervals();
	for (int number : Note::typeNums.at(mode)) {
		for (int interval : *intervals) {
			if ((interval + number) == note) {
				return true;
			}
		}
	}
	return false;
}
