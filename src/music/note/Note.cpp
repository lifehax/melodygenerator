#include "stdafx.h"

#include <algorithm>
#include <functional>
#include <iostream>

#include "Note.h"

const std::vector<NoteDef>  Note::notes = {
	{ "C0", 16.3516 },{ "C#0", 17.3239 },{ "D0", 18.354 },{ "Eb0", 19.4454 },{ "E0", 20.6017 },{ "F0", 21.8268 },{ "F#0", 23.1247 },{ "G0", 24.4997 },{ "G#0", 25.9565 },{ "A0", 27.5 },{ "Bb0", 29.1352 },{ "B0", 30.8677 },
	{ "C1", 32.7032 },{ "C#1", 34.6478 },{ "D1", 36.7081 },{ "Eb1", 38.8909 },{ "E1", 41.2034 },{ "F1", 43.6535 },{ "F#1", 46.2493 },{ "G1", 48.9994 },{ "G#1", 51.9131 },{ "A1", 55 },{ "Bb1", 58.2705 },{ "B1", 61.7354 },
	{ "C2", 65.4064 },{ "C#2", 69.2957 },{ "D2", 73.4162 },{ "Eb2", 77.7817 },{ "E2", 82.4069 },{ "F2", 87.3071 },{ "F#2", 92.4986 },{ "G2", 97.9989 },{ "G#2", 103.826 },{ "A2", 110 },{ "Bb2", 116.541 },{ "B2", 123.471 },
	{ "C3", 130.813 },{ "C#3", 138.591 },{ "D3", 146.832 },{ "Eb3", 155.563 },{ "E3", 164.814 },{ "F3", 174.614 },{ "F#3", 184.997 },{ "G3", 195.998 },{ "G#3", 207.652 },{ "A3", 220 },{ "Bb3", 233.082 },{ "B3", 246.942 },
	{ "C4", 261.626 },{ "C#4", 277.183 },{ "D4", 293.665 },{ "Eb4", 311.127 },{ "E4", 329.628 },{ "F4", 349.228 },{ "F#4", 369.994 },{ "G4", 391.995 },{ "G#4", 415.305 },{ "A4", 440 },{ "Bb4", 466.164 },{ "B4", 493.883 },
	{ "C5", 523.251 },{ "C#5", 554.365 },{ "D5", 587.33 },{ "Eb5", 622.254 },{ "E5", 659.255 },{ "F5", 698.456 },{ "F#5", 739.989 },{ "G5", 783.991 },{ "G#5", 830.609 },{ "A5", 880 },{ "Bb5", 932.328 },{ "B5", 987.767 },
	{ "C6", 1046.5 },{ "C#6", 1108.73 },{ "D6", 1174.66 },{ "Eb6", 1244.51 },{ "E6", 1318.51 },{ "F6", 1396.91 },{ "F#6", 1479.98 },{ "G6", 1567.98 },{ "G#6", 1661.22 },{ "A6", 1760 },{ "Bb6", 1864.66 },{ "B6", 1975.53 },
	{ "C7", 2093 },{ "C#7", 2217.46 },{ "D7", 2349.32 },{ "Eb7", 2489.02 },{ "E7", 2637.02 },{ "F7", 2793.83 },{ "F#7", 2959.96 },{ "G7", 3135.96 },{ "G#7", 3322.44 },{ "A7", 3520 },{ "Bb7", 3729.31 },{ "B7", 3951.07 },
	{ "C8", 4186.01 },{ "C#8", 4434.92 },{ "D8", 4698.64 },{ "Eb8", 4978.03 },{ "E8", 5274.04 },{ "F8", 5587.65 },{ "F#8", 5919.91 },{ "G8", 6271.93 },{ "G#8", 6644.88 },{ "A8", 7040 },{ "Bb8", 7458.62 },{ "B8", 7902.13 },
	{ "blank", 0 }
};

const std::vector<std::string> Note::allNotes = {
	"C0","C#0","D0","Eb0","E0","F0","F#0","G0","G#0","A0","Bb0","B0",
	"C1","C#1","D1","Eb1","E1","F1","F#1","G1","G#1","A1","Bb1","B1",
	"C2","C#2","D2","Eb2","E2","F2","F#2","G2","G#2","A2","Bb2","B2",
	"C3","C#3","D3","Eb3","E3","F3","F#3","G3","G#3","A3","Bb3","B3",
	"C4","C#4","D4","Eb4","E4","F4","F#4","G4","G#4","A4","Bb4","B4",
	"C5","C#5","D5","Eb5","E5","F5","F#5","G5","G#5","A5","Bb5","B5",
	"C6","C#6","D6","Eb6","E6","F6","F#6","G6","G#6","A6","Bb6","B6",
	"C7","C#7","D7","Eb7","E7","F7","F#7","G7","G#7","A7","Bb7","B7",
	"C8","C#8","D8","Eb8","E8","F8","F#8","G8","G#8","A8","Bb8","B8",
	"blank"
};
const std::map<std::string, int> Note::idxMap = {
	{ "C0",  0 },{ "C#0",  1 },{ "D0",  2 },{ "Eb0",  3 },{ "E0",   4 },{ "F0",   5 },{ "F#0",   6 },{ "G0",   7 },{ "G#0",   8 },{ "A0",   9 },{ "Bb0",  10 },{ "B0",  11 },
	{ "C1", 12 },{ "C#1", 13 },{ "D1", 14 },{ "Eb1", 15 },{ "E1",  16 },{ "F1",  17 },{ "F#1",  18 },{ "G1",  19 },{ "G#1",  20 },{ "A1",  21 },{ "Bb1",  22 },{ "B1",  23 },
	{ "C2", 24 },{ "C#2", 25 },{ "D2", 26 },{ "Eb2", 27 },{ "E2",  28 },{ "F2",  29 },{ "F#2",  30 },{ "G2",  31 },{ "G#2",  32 },{ "A2",  33 },{ "Bb2",  34 },{ "B2",  35 },
	{ "C3", 36 },{ "C#3", 37 },{ "D3", 38 },{ "Eb3", 39 },{ "E3",  40 },{ "F3",  41 },{ "F#3",  42 },{ "G3",  43 },{ "G#3",  44 },{ "A3",  45 },{ "Bb3",  46 },{ "B3",  47 },
	{ "C4", 48 },{ "C#4", 49 },{ "D4", 50 },{ "Eb4", 51 },{ "E4",  52 },{ "F4",  53 },{ "F#4",  54 },{ "G4",  55 },{ "G#4",  56 },{ "A4",  57 },{ "Bb4",  58 },{ "B4",  59 },
	{ "C5", 60 },{ "C#5", 61 },{ "D5", 62 },{ "Eb5", 63 },{ "E5",  64 },{ "F5",  65 },{ "F#5",  66 },{ "G5",  67 },{ "G#5",  68 },{ "A5",  69 },{ "Bb5",  70 },{ "B5",  71 },
	{ "C6", 72 },{ "C#6", 73 },{ "D6", 74 },{ "Eb6", 75 },{ "E6",  76 },{ "F6",  77 },{ "F#6",  78 },{ "G6",  79 },{ "G#6",  80 },{ "A6",  81 },{ "Bb6",  82 },{ "B6",  83 },
	{ "C7", 84 },{ "C#7", 85 },{ "D7", 86 },{ "Eb7", 87 },{ "E7",  88 },{ "F7",  89 },{ "F#7",  90 },{ "G7",  91 },{ "G#7",  92 },{ "A7",  93 },{ "Bb7",  94 },{ "B7",  95 },
	{ "C8", 96 },{ "C#8", 97 },{ "D8", 98 },{ "Eb8", 99 },{ "E8", 100 },{ "F8", 101 },{ "F#8", 102 },{ "G8", 103 },{ "G#8", 104 },{ "A8", 105 },{ "Bb8", 106 },{ "B8", 107 },
	{ "blank", 108 }
};

const std::map<std::string, std::vector<int>> Note::typeNums = {
	{ "C",  { 0,  12, 24, 36, 48, 60, 72, 84, 96  } },
	{ "C#", { 1,  13, 25, 37, 49, 61, 73, 85, 97  } },
	{ "D",  { 2,  14, 26, 38, 50, 62, 74, 86, 98  } },
	{ "Eb", { 3,  15, 27, 39, 51, 63, 75, 87, 99  } },
	{ "E",  { 4,  16, 28, 40, 52, 64, 76, 88, 100 } },
	{ "F",  { 5,  17, 29, 41, 53, 65, 77, 89, 101 } },
	{ "F#", { 6,  18, 30, 42, 54, 66, 78, 90, 102 } },
	{ "G",  { 7,  19, 31, 43, 55, 67, 79, 91, 103 } },
	{ "G#", { 8,  20, 32, 44, 56, 68, 80, 92, 104 } },
	{ "A",  { 9,  21, 33, 45, 57, 69, 81, 93, 105 } },
	{ "Bb", { 10, 22, 34, 46, 58, 70, 82, 94, 106 } },
	{ "B",  { 11, 23, 35, 47, 59, 71, 83, 95, 107 } }
};

const std::vector<std::string> Note::leadToFollowNotes = {
	"C4","C#4","D4","Eb4","E4","F4","F#4","G4","G#4","A4","Bb4","B4",
	"C3","C#3","D3","Eb3","E3","F3","F#3","G3","G#3","A3","Bb3","B3",
	"C5","C#5","D5","Eb5","E5","F5","F#5","G5","G#5","A5","Bb5","B5",
	"C2","C#2","D2","Eb2","E2","F2","F#2","G2","G#2","A2","Bb2","B2",
	"C6","C#6","D6","Eb6","E6","F6","F#6","G6","G#6","A6","Bb6","B6",
	"C7","C#7","D7","Eb7","E7","F7","F#7","G7","G#7","A7","Bb7","B7",
	"C1","C#1","D1","Eb1","E1","F1","F#1","G1","G#1","A1","Bb1","B1",
	"C0","C#0","D0","Eb0","E0","F0","F#0","G0","G#0","A0","Bb0","B0",
	"C8","C#8","D8","Eb8","E8","F8","F#8","G8","G#8","A8","Bb8","B8"
};
const std::vector<std::string> Note::halfNotes = {
	"C#0","Eb0","F#0","G#0","Bb0",
	"C#1","Eb1","F#1","G#1","Bb1",
	"C#2","Eb2","F#2","G#2","Bb2",
	"C#3","Eb3","F#3","G#3","Bb3",
	"C#4","Eb4","F#4","G#4","Bb4",
	"C#5","Eb5","F#5","G#5","Bb5",
	"C#6","Eb6","F#6","G#6","Bb6",
	"C#7","Eb7","F#7","G#7","Bb7",
	"C#8","Eb8","F#8","G#8","Bb8"
};
const std::vector<std::string> Note::wholeNotes = {
	"C0", "D0", "E0", "F0", "G0", "A0", "B0",
	"C1", "D1", "E1", "F1", "G1", "A1", "B1",
	"C2", "D2", "E2", "F2", "G2", "A2", "B2",
	"C3", "D3", "E3", "F3", "G3", "A3", "B3",
	"C4", "D4", "E4", "F4", "G4", "A4", "B4",
	"C5", "D5", "E5", "F5", "G5", "A5", "B5",
	"C6", "D6", "E6", "F6", "G6", "A6", "B6",
	"C7", "D7", "E7", "F7", "G7", "A7", "B7",
	"C8", "D8", "E8", "F8", "G8", "A8", "B8"
};

bool Note::isAugmentedFifth(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 7;
}

bool Note::isPerfectFifth(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 6;
}

bool Note::isDiminishedFifth(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 5;
}

bool Note::isPerfectFourth(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 4;
}

bool Note::isMajorThird(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 3;
}

bool Note::isMinorThird(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 2;
}

bool Note::isOctave(std::string note1, std::string note2) {
	int note1Pos = idxMap.find(note1)->second;
	int note2Pos = idxMap.find(note2)->second;

	return abs(note1Pos - note2Pos) % 12 == 0 && note1Pos - note2Pos != 0;
}

std::pair<int, int> * Note::pitchRatio(std::string note1name, std::string note2name) {
	int note1Idx = idxMap.find(note1name)->second;
	int note2Idx = idxMap.find(note2name)->second;
	auto note1 = notes[note1Idx];
	auto note2 = notes[note2Idx];

	double frequency1 = (std::pow(2.0, (note1Idx - 57.0) / 12.0)) * 440.0;
	double frequency2 = (std::pow(2.0, (note2Idx - 57.0) / 12.0)) * 440.0;
	if (frequency1 > frequency2) {
		double freqSwap = frequency1;
		frequency1 = frequency2;
		frequency2 = freqSwap;
	}

	return new std::pair<int, int>(0, 0);
}
