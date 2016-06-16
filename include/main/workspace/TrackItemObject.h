#pragma once

#include <string>
#include <vector>
#include <map>

enum class TrackItemType { NOTE, CHORD, HARMONOUS_NOTE };

class TrackItemObject {
protected:
	TrackItemType type;

	std::string melodyGroup;
	std::vector<std::string> * melodies;
	std::map<std::string, std::string> * metaInformation;

	int64_t trackTime;
	int midiInstrument;
	int length;
public:
	TrackItemObject(int64_t, int, TrackItemType);

	virtual void setMelodyGroup(std::string);
	std::string getMelodyGroup();

	void setMetaInformation(std::string, std::string);
	std::map<std::string, std::string> * getMetaInformation();

	void addMelody(std::string name);
	bool isForMelody(std::string name);
	std::vector<std::string> * getMelodies();

	int64_t getTrackTime();
	virtual void setTrackTime(int64_t);

	virtual void setInstrument(int);
	int getInstrument();

	int getLength();
	virtual void setLength(int);

	bool isType(TrackItemType);
	bool isNote();
	bool isChord();
	virtual void setNoteByNumber(int) = 0;
	virtual int getNumber() = 0;
};
