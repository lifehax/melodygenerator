#pragma once

#include <boost/tuple/tuple.hpp>
#include "TrackItem.h"
#include "TrackItemObject.h"

enum class TrackChordVariable {
	NOTE = 0,
	ROOT = 1,
	RELATIVE_DIFFERENCE = 2
};

class TrackChord : public TrackItemObject {
protected:
	int root;
	std::string degree;

	std::vector<boost::tuple<
		TrackNote *,
		bool,
		int
	>> * notes;

public:
	TrackChord(int64_t time, int root, std::string degree, int length);

	void setNotes();
	std::vector<TrackNote *> * getNotes();

	std::string getDegree();
	void setDegree(std::string);

	int getRootNote();
	virtual int getNumber();
	void setRootNote(int);
	virtual void setNoteByNumber(int);

	void removeAllNotes();

	virtual void setMelodyGroup(std::string noteMelodyGroup);
	virtual void setTrackTime(int64_t trackTime);
	virtual void setInstrument(int instrument);
	virtual void setLength(int length);
};
