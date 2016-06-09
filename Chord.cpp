#include "stdafx.h"

#include <string>
#include <cassert>

#include "Chord.h"
#include "Note.h"

std::map<std::string, std::string> Chord::ChordNames {
	{ "I",       "MajorTonic" },
	{ "i",       "MinorTonic" },
	{ "ii",      "MinorSuperTonic" },
	{ "III",     "MajorMediant" },
	{ "bIII",    "FlatMajorMediant" },
	{ "iii",     "MinorMediant" },
	{ "IV",      "MajorSubdominant" },
	{ "iv",      "MinorSubdominant" },
	{ "V",       "MajorDominant" },
	{ "v",       "MinorDominant" },
	{ "VI",      "MajorSubMediant" },
	{ "bVI",     "FlatMajorSubMediant" },
	{ "vi",      "MinorSubMediant" },
	{ "bVII",    "FlatMajorSubTonic" }
};

std::map<std::string, int> Chord::ChordDegreeAmounts {
	{ "I",       0 },
	{ "i",       0 },
	{ "ii",      2 },
	{ "III",     4 },
	{ "bIII",    3 },
	{ "iii",     4 },
	{ "IV",      5 },
	{ "iv",      5 },
	{ "V",       7 },
	{ "v",       7 },
	{ "VI",      9 },
	{ "bVI",     8 },
	{ "vi",      9 },
	{ "bVII",    10 }
};

std::vector<std::string> Chord::Chords{ "I", "i", "ii", "III", "bIII", "ii", "IV", "iv", "V", "v", "VI", "bVI", "vi", "bVII" };

std::vector<int> * Chord::GetMajorTriad(int root) {
	std::vector<int> * chordNotes = new std::vector<int>();
	chordNotes->push_back(root);
	chordNotes->push_back(root + 4);
	chordNotes->push_back(root + 7);
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetChord(std::string notation, int scalePosition) {
	if (notation == "I") {
		return GetMajorTriadTonic(scalePosition);
	} else if (notation == "i") {
		return GetMinorTriadTonic(scalePosition);
	} else if (notation == "ii") {
		return GetMinorTriadSuperTonic(scalePosition);
	} else if (notation == "III") {
		return GetMajorTriadMediant(scalePosition);
	} else if (notation == "bIII") {
		return GetFlatMajorTriadMediant(scalePosition);
	} else if (notation == "iii") {
		return GetMinorTriadMediant(scalePosition);
	} else if (notation == "IV") {
		return GetMajorTriadSubdominant(scalePosition);
	} else if (notation == "iv") {
		return GetMinorTriadSubdominant(scalePosition);
	} else if (notation == "V") {
		return GetMajorTriadDominant(scalePosition);
	} else if (notation == "v") {
		return GetMinorTriadDominant(scalePosition);
	} else if (notation == "VI") {
		return GetMajorTriadSubMediant(scalePosition);
	} else if (notation == "bVI") {
		return GetFlatMajorTriadSubMediant(scalePosition);
	} else if (notation == "vi") {
		return GetMinorTriadSubMediant(scalePosition);
	} else if (notation == "bVII") {
		return GetFlatMajorTriadSubTonic(scalePosition);
	}
	assert(true);
	return NULL;
}
std::vector<std::pair<int, bool>> * Chord::GetMajorTriadTonic(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition, true });
	chordNotes->push_back({ scalePosition + 4, false });
	chordNotes->push_back({ scalePosition + 7, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadTonic(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition, true });
	chordNotes->push_back({ scalePosition + 3, false });
	chordNotes->push_back({ scalePosition + 7, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadSuperTonic(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 2, true });
	chordNotes->push_back({ scalePosition + 6, false });
	chordNotes->push_back({ scalePosition + 9, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMajorTriadMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 4,  true });
	chordNotes->push_back({ scalePosition + 8,  false });
	chordNotes->push_back({ scalePosition + 11, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetFlatMajorTriadMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 3,  true });
	chordNotes->push_back({ scalePosition + 7,  false });
	chordNotes->push_back({ scalePosition + 10, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 4,  true });
	chordNotes->push_back({ scalePosition + 7,  false });
	chordNotes->push_back({ scalePosition + 11, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMajorTriadSubdominant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 5,  true });
	chordNotes->push_back({ scalePosition + 9,  false });
	chordNotes->push_back({ scalePosition + 12, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadSubdominant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 5,  true });
	chordNotes->push_back({ scalePosition + 8,  false });
	chordNotes->push_back({ scalePosition + 12, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMajorTriadDominant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 7,  true });
	chordNotes->push_back({ scalePosition + 11, false });
	chordNotes->push_back({ scalePosition + 14, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadDominant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 7,  true });
	chordNotes->push_back({ scalePosition + 10, false });
	chordNotes->push_back({ scalePosition + 14, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMajorTriadSubMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 9,  true });
	chordNotes->push_back({ scalePosition + 13, false });
	chordNotes->push_back({ scalePosition + 16, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetFlatMajorTriadSubMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 8,  true });
	chordNotes->push_back({ scalePosition + 12, false });
	chordNotes->push_back({ scalePosition + 15, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetMinorTriadSubMediant(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 9,  true });
	chordNotes->push_back({ scalePosition + 12, false });
	chordNotes->push_back({ scalePosition + 16, false });
	return chordNotes;
}

std::vector<std::pair<int, bool>> * Chord::GetFlatMajorTriadSubTonic(int scalePosition) {
	std::vector<std::pair<int, bool>> * chordNotes = new std::vector<std::pair<int, bool>>();
	chordNotes->push_back({ scalePosition + 10, true });
	chordNotes->push_back({ scalePosition + 14, false });
	chordNotes->push_back({ scalePosition + 17, false });
	return chordNotes;
}

std::vector<std::string> * Chord::ChordsInScale(Scale * scale) {
	std::vector<std::string> * possibleChords = new std::vector<std::string>();
	for (auto chord : Chord::Chords) {
		std::vector<std::string> * modes = scale->getModes();
		for (auto mode : *modes) {
			std::vector<int> * modeNotes = scale->getModeNotes(mode);
			std::string rootInMode = mode + "4";
			int rootNoteIdx = Note::idxMap.at(rootInMode);
			std::vector<std::pair<int, bool>> * notes = Chord::GetChord(chord, rootNoteIdx);
			bool allFound = true;
			for (auto note : *notes) {
				if (std::find(modeNotes->begin(), modeNotes->end(), note.first) == modeNotes->end()) {
					allFound &= false;
					break;
				}
			}
			if (allFound) {
				possibleChords->push_back(chord);
			}
		}
	}
	return possibleChords;
}

std::vector<std::string> * Chord::ChordsInScaleMode(Scale * scale, std::string mode) {
	std::vector<std::string> * possibleChords = new std::vector<std::string>();
	std::vector<int> * modeNotes = scale->getModeNotes(mode);
	std::string rootInMode = mode + "4";
	int rootNoteIdx = Note::idxMap.at(rootInMode);
	for (auto chord : Chord::Chords) {
		std::vector<std::pair<int, bool>> * notes = Chord::GetChord(chord, rootNoteIdx);
		bool allFound = true;
		for (auto note : *notes) {
			if (std::find(modeNotes->begin(), modeNotes->end(), note.first) == modeNotes->end()) {
				allFound &= false;
				break;
			}
		}
		if (allFound) {
			possibleChords->push_back(chord);
		}
	}
	return possibleChords;
}
