#pragma once

#include "Track.h"

class MIDITrack : public Track {
protected:
	double beatsPerBar;
	int noteDivision;
	int defaultInstrument;
	int tempo;

	std::map<int64_t, std::vector<TrackItem *> *> * notesMap;
public:
	MIDITrack();

	void setBeatsPerBar(double);
	double getBeatsPerBar();
	void setNoteDivision(int);
	int getNoteDivision();
	void setDefaultInstrument(int);
	int getDefaultInstrument();

	void addItem(TrackItem *);
	void removeItem(TrackItem *);
	void addItems(std::vector<TrackItem *> *);

	void setTempo(int);
	int getTempo();

	virtual std::wstring getFileName(std::wstring);
	virtual void saveInfoHtml(std::wstring);
	void saveMIDI(std::wstring);

	std::map<int64_t, std::vector<TrackItem *> *> * getTrackMap();

	int64_t size();
	int64_t sizeForMelody(std::string);

	std::vector<TrackItem *> * getMostRecentNotes();
	std::vector<TrackItem *> * getMostRecentNotesForMelody(std::string);
	TrackItem * getMostRecentNoteForUniqueNoteMelody(std::string);

	std::vector<TrackItem *> * getNotesAtTime(int64_t time);
	std::vector<TrackItem *> * getNotesAtTimeForMelody(int64_t time, std::string);
	std::vector<TrackItem *> * getNotesAtTimeForMelodies(int64_t time, std::vector<std::string> * melodies);
	std::vector<TrackItem *> * getAllNotesForMelody(std::string);
	std::vector<TrackItem *> * getAllNotesForMelodyGroup(std::string);
};
