#pragma once

#include <string>
#include <vector>
#include <map>

class TrackNote;
class TrackChord;

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
	virtual void setNoteByNumber(int) = 0;
	virtual int getNumber() = 0;
};

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