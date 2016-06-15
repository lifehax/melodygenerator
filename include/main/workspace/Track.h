#pragma once

#include "map"
#include "vector"
#include "TrackItem.h"
#include "TrackNote.h"
#include "TrackChord.h"

class Track {
private:
	std::string name;
public:
	Track();

	virtual std::wstring getFileName(std::wstring) = 0;
	virtual void saveInfoHtml(std::wstring) = 0;

	void setName(std::string);
	std::string getName();
};
