#pragma once

#include <string>
#include <vector>

#include "MIDITrack.h"
#include "TrackNote.h"

class Harmony {
public:
	enum class HarmonyType {
		MINOR_SECOND_INTERVAL,
		MAJOR_SECOND_INTERVAL,
		MINOR_THIRD_INTERVAL,
		MAJOR_THIRD_INTERVAL,
		PERFECT_FOURTH_INTERVAL,
		PERFECT_FIFTH_INTERVAL,
		MINOR_SIXTH_INTERVAL,
		MAJOR_SIXTH_INTERVAL,
		MINOR_SEVENTH_INTERVAL,
		MAJOR_SEVENTH_INTERVAL,
		PERFECT_OCTAVE_INTERVAL,
		NOT_SAME_NOTE
	};
private:
	std::vector<TrackItem *> * harmonizeWithAtTime;
	int64_t currentTimeCache;
	std::vector<Harmony::HarmonyType> harmonizeAs;
	MIDITrack * forTrack;
public:
	Harmony(MIDITrack * forTrack, std::vector<Harmony::HarmonyType> harmonizeAs);

	bool isHarmonicWithTime(int note, int64_t trackTime);
	bool isHarmonicWithNotesAtTime(int note, std::vector<TrackItem *> * harmonizeWith);
	bool isHarmonicWithNotes(TrackItem * note, std::vector<TrackItem *> * harmonizeWith);

	const static std::map<Harmony::HarmonyType, int> intervalAmounts;
};
