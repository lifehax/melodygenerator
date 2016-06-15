#pragma once

#include "vector"

class Scale {
public:
	virtual std::vector<int> *  getIntervals() = 0;
	virtual std::vector<std::string> *  getModes() = 0;
	virtual std::string getName() = 0;

	std::vector<int> *  getNotes(int startNote);
	std::vector<int> *  getAllNotes();
	std::vector<int> *  getModeNotes(std::string mode);
	bool isValidNoteInScale(int note);
	bool isValidNoteInScaleMode(int note, std::string mode);
};
