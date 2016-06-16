#pragma once

#include <string>
#include <vector>
#include <map>

class TrackNote;
class TrackChord;

#include "TrackItemObject.h"

class TrackItem {
protected:
	TrackItemObject * object;

public:
	TrackItem(TrackItemObject *);

	void setMelodyGroup(std::string);
	std::string getMelodyGroup();

	void setMetaInformation(std::string, std::string);
	std::map<std::string, std::string> * getMetaInformation();

	void addMelody(std::string name);
	bool isForMelody(std::string name);
	std::vector<std::string> * getMelodies();

	int64_t getTrackTime();
	void setTrackTime(int64_t);

	void setInstrument(int);
	int getInstrument();

	int getLength();
	void setLength(int);

	std::vector<TrackNote *> * getAllNotes();

	bool isType(TrackItemType);
	bool isNote();
	bool isChord();
	void setNoteByNumber(int);
	int getNumber();

	static TrackItem * CreateNote(int64_t, int, int);
	static TrackItem * CreateChord(int64_t, int, int, std::string);
	static bool HasTimeOverlap(TrackItem *, TrackItem *);

	template<typename Type>
	Type * getObject() {
		return (Type *)this->object;
	}

	void switchToChord(std::string);
	void switchToNote();
};