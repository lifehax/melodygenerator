#pragma once
#include <string>

#include "Type.h"
#include "Melody.h"

class SongGenerator;

class TwoMelodySingleNoteRandomType : public Type {
public:
	TwoMelodySingleNoteRandomType(int number, std::wstring name);
	virtual int getBpm();
	virtual int getMicroSecondsPerNote();
	virtual int64_t getSongLength();
	virtual SongGenerator * getGenerator(MIDITrack * target);
	virtual std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * getOptions();
};
