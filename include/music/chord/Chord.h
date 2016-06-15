#pragma once

#include "map"
#include "vector"
#include "Scale.h"

class Chord {
public:
	static std::map<std::string, std::string> ChordNames;
	static std::vector<std::string> Chords;
	static std::map<std::string, int> ChordDegreeAmounts;
	static std::vector<int> * GetMajorTriad(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMajorTriadTonic(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadTonic(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadSuperTonic(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMajorTriadMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetFlatMajorTriadMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMajorTriadSubdominant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadSubdominant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMajorTriadDominant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadDominant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMajorTriadSubMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetFlatMajorTriadSubMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetMinorTriadSubMediant(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetFlatMajorTriadSubTonic(int scalePosition);
	static std::vector<std::pair<int, bool>> * GetChord(std::string notation, int scalePosition);
	static std::vector<std::string> * ChordsInScale(Scale *);
	static std::vector<std::string> * ChordsInScaleMode(Scale *, std::string);
};