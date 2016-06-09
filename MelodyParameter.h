#pragma once

#include <functional>
#include <map>
#include <vector>
#include "TrackNote.h"

#define PI 3.14159265

class ModularMelody;
class Scale;

typedef std::function<int(ModularMelody *, std::vector<TrackItem *> *, int, int64_t)> ModulatorFunction;

enum class MelodyParameterType {
	PRIORITY,
	NOTE_LENGTH,
	SONG_LENGTH,
	MODULATOR,
	ROOT_NOTE,
	LENGTH,
	SIZE,
	TRACK_TIME,
	SCALE,
	SCALE_MODE,
	RHYTHM,
	MODULATION_FUNCTION,
	HARMONIZER,
	UPPER_NOTE_LIMIT,
	LOWER_NOTE_LIMIT,
	MELODY_REPEAT_SIZE,
	HARMONY_MODE,
	MODULATION_PATTERN,
	MAX_SHIFT,
	MELODY_GROUP,
	CHORD_REHARMONIZE_MODE,
	INSTRUMENT,
	LEAD_MELODY,
	FOLLOW_DISTANCE
};

enum class ChordReharmonizeMode {
	RANDOM,
	CLOSEST,
	REMOVE
};

extern std::map<MelodyParameterType, std::string> MelodyParameterTypeStrMap;

class MelodyParameterID {
protected:
	static int currentParamIdentifier;
public:
	static std::string NextParamIdentifier() {
		return "TBParam" + std::to_string(currentParamIdentifier++);
	}
};

template <class PT>
class MelodyParameter {
protected:
	std::string id;
	MelodyParameterType param;
	PT value;

public:
	MelodyParameter(std::string id, MelodyParameterType param, PT value) {
		this->id = id;
		this->param = param;
		this->value = value;
	}

	std::string getID() {
		return this->id;
	}

	MelodyParameterType getParameterType() {
		return this->param;
	}

	PT getParameterValue() {
		return this->value;
	}

	void setParameterValue(PT value) {
		this->value = value;
	}

};

#include "ModulatorFunctions.h"

