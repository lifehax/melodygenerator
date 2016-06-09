#pragma once

#include <string>
#include <vector>
#include <map>
#include "TrackItem.h"

class TrackNote : public TrackItemObject {
protected:
	std::string note;
	int db;
	double freq;
	int number;

public:
	TrackNote(int64_t time, int note, int length);

	std::string getNote();
	void setNote(std::string);

	virtual int getNumber();
	virtual void setNoteByNumber(int);

	double getFreq();
	void setFreq(double);

	int getDB();
	void setDB(int);

	bool equals(TrackNote *);

	static bool SortByNumber(TrackNote * a, TrackNote * b) {
		return a->getNumber() < b->getNumber();
	}
};