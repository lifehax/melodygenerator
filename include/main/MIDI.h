#pragma once
#include <map>
#include <iostream>
#include <fstream>
#include <string>

class MIDITrack;
class TrackNote;

class MIDI {
private:
	MIDITrack * track;
	std::ofstream midiFile;
	std::wstring fileName;
public:
	MIDI(MIDITrack *, std::wstring);
	void save();

	static bool MIDI::sortReleaseKeys(std::pair<int, std::pair<int64_t, TrackNote *> *> * i, std::pair<int, std::pair<int64_t, TrackNote *> *> * j);
	static std::map<int, std::string> instruments;
	static std::map<std::string, int> noteNumbers;
};