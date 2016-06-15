#include "stdafx.h"

#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include <vector>
#include <map>
#include <iostream>
#include <fstream>

#include "MIDI.h"
#include "MIDITrack.h"
#include "TrackNote.h"

#include "jdksmidi/world.h"
#include "jdksmidi/track.h"
#include "jdksmidi/multitrack.h"
#include "jdksmidi/filereadmultitrack.h"
#include "jdksmidi/fileread.h"
#include "jdksmidi/fileshow.h"
#include "jdksmidi/filewritemultitrack.h"

std::map<int, std::string> MIDI::instruments {
	{ 1,"Acoustic Grand Piano" },
	{ 2,"Bright Acoustic Piano" },
	{ 3,"Electric Grand Piano" },
	{ 4,"Honky-tonk Piano" },
	{ 5,"Rhodes Piano" },
	{ 6,"Chorused Piano" },
	{ 7,"Harpsichord" },
	{ 8,"Clavinet" },
	{ 9,"Celesta" },
	{ 10,"Glockenspiel" },
	{ 11,"Music Box" },
	{ 12,"Vibraphone" },
	{ 13,"Marimba" },
	{ 14,"Xylophone" },
	{ 15,"Tubular Bells" },
	{ 16,"Dulcimer" },
	{ 17,"Hammond Organ" },
	{ 18,"Percussive Organ" },
	{ 19,"Rock Organ" },
	{ 20,"Church Organ" },
	{ 21,"Reed Organ" },
	{ 22,"Accordion" },
	{ 23,"Harmonica" },
	{ 24,"Tango Accordion" },
	{ 25,"Acoustic Nylon Guitar" },
	{ 26,"Acoustic Steel Guitar" },
	{ 27,"Electric Jazz Guitar" },
	{ 28,"Electric Clean Guitar" },
	{ 29,"Electric Muted Guitar" },
	{ 30,"Overdriven Guitar" },
	{ 31,"Distortion Guitar" },
	{ 32,"Guitar Harmonics" },
	{ 33,"Acoustic Bass" },
	{ 34,"Fingered Electric Bass" },
	{ 35,"Plucked Electric Bass" },
	{ 36,"Fretless Bass" },
	{ 37,"Slap Bass 1" },
	{ 38,"Slap Bass 2" },
	{ 39,"Synth Bass 1" },
	{ 40,"Synth Bass 2" },
	{ 41,"Violin" },
	{ 42,"Viola" },
	{ 43,"Cello" },
	{ 44,"Contrabass" },
	{ 45,"Tremolo Strings" },
	{ 46,"Pizzicato Strings" },
	{ 47,"Orchestral Harp" },
	{ 48,"Timpani" },
	{ 49,"String Ensemble 1" },
	{ 50,"String Ensemble 2" },
	{ 51,"Synth Strings 1" },
	{ 52,"Synth Strings 2" },
	{ 53,"Choir Aah" },
	{ 54,"Choir Ooh" },
	{ 55,"Synth Voice" },
	{ 56,"Orchestral Hit" },
	{ 57,"Trumpet" },
	{ 58,"Trombone" },
	{ 59,"Tuba" },
	{ 60,"Muted Trumpet" },
	{ 61,"French Horn" },
	{ 62,"Brass Section" },
	{ 63,"Synth Brass 1" },
	{ 64,"Synth Brass 2" },
	{ 65,"Soprano Sax" },
	{ 66,"Alto Sax" },
	{ 67,"Tenor Sax" },
	{ 68,"Baritone Sax" },
	{ 69,"Oboe" },
	{ 70,"English Horn" },
	{ 71,"Bassoon" },
	{ 72,"Clarinet" },
	{ 73,"Piccolo" },
	{ 74,"Flute" },
	{ 75,"Recorder" },
	{ 76,"Pan Flute" },
	{ 77,"Bottle Blow" },
	{ 78,"Shakuhachi" },
	{ 79,"Whistle" },
	{ 80,"Ocarina" },
	{ 81,"Square Wave Lead" },
	{ 82,"Sawtooth Wave Lead" },
	{ 83,"Calliope Lead" },
	{ 84,"Chiff Lead" },
	{ 85,"Charang Lead" },
	{ 86,"Voice Lead" },
	{ 87,"Fifths Lead" },
	{ 88,"Bass Lead" },
	{ 89,"New Age Pad" },
	{ 90,"Warm Pad" },
	{ 91,"Polysynth Pad" },
	{ 92,"Choir Pad" },
	{ 93,"Bowed Pad" },
	{ 94,"Metallic Pad" },
	{ 95,"Halo Pad" },
	{ 96,"Sweep Pad" },
	{ 97,"Rain Effect" },
	{ 98,"Soundtrack Effect" },
	{ 99,"Crystal Effect" },
	{ 100,"Atmosphere Effect" },
	{ 101,"Brightness Effect" },
	{ 102,"Goblins Effect" },
	{ 103,"Echoes Effect" },
	{ 104,"Sci-Fi Effect" },
	{ 105,"Sitar" },
	{ 106,"Banjo" },
	{ 107,"Shamisen" },
	{ 108,"Koto" },
	{ 109,"Kalimba" },
	{ 110,"Bagpipe" },
	{ 111,"Fiddle" },
	{ 112,"Shanai" },
	{ 113,"Tinkle Bell" },
	{ 114,"Agogo" },
	{ 115,"Steel Drums" },
	{ 116,"Woodblock" },
	{ 117,"Taiko Drum" },
	{ 118,"Melodic Tom" },
	{ 119,"Synth Drum" },
	{ 120,"Reverse Cymbal" },
	{ 121,"Guitar Fret Noise" },
	{ 122,"Breath Noise" },
	{ 123,"Seashore" },
	{ 124,"Bird Tweet" },
	{ 125,"Telephone Ring" },
	{ 126,"Helicopter" },
	{ 127,"Applause" },
	{ 128,"Gun Shot" }
};

std::map<std::string, int> MIDI::noteNumbers {
	{ "C0", 12 },
	{ "C#0", 13 },
	{ "D0", 14 },
	{ "Eb0", 15 },
	{ "E0", 16 },
	{ "F0", 17 },
	{ "F#0", 18 },
	{ "G0", 19 },
	{ "G#0", 20 },
	{ "A0", 21 },
	{ "Bb0", 22 },
	{ "B0", 23 },
	{ "C1", 24 },
	{ "C#1", 25 },
	{ "D1", 26 },
	{ "Eb1", 27 },
	{ "E1", 28 },
	{ "F1", 29 },
	{ "F#1", 30 },
	{ "G1", 31 },
	{ "G#1", 32 },
	{ "A1", 33 },
	{ "Bb1", 34 },
	{ "B1", 35 },
	{ "C2", 36 },
	{ "C#2", 37 },
	{ "D2", 38 },
	{ "Eb2", 39 },
	{ "E2", 40 },
	{ "F2", 41 },
	{ "F#2", 42 },
	{ "G2", 43 },
	{ "G#2", 44 },
	{ "A2", 45 },
	{ "Bb2", 46 },
	{ "B2", 47 },
	{ "C3", 48 },
	{ "C#3", 49 },
	{ "D3", 50 },
	{ "Eb3", 51 },
	{ "E3", 52 },
	{ "F3", 53 },
	{ "F#3", 54 },
	{ "G3", 55 },
	{ "G#3", 56 },
	{ "A3", 57 },
	{ "Bb3", 58 },
	{ "B3", 59 },
	{ "C4", 60 },
	{ "C#4", 61 },
	{ "D4", 62 },
	{ "Eb4", 63 },
	{ "E4", 64 },
	{ "F4", 65 },
	{ "F#4", 66 },
	{ "G4", 67 },
	{ "G#4", 68 },
	{ "A4", 69 },
	{ "Bb4", 70 },
	{ "B4", 71 },
	{ "C5", 72 },
	{ "C#5", 73 },
	{ "D5", 74 },
	{ "Eb5", 75 },
	{ "E5", 76 },
	{ "F5", 77 },
	{ "F#5", 78 },
	{ "G5", 79 },
	{ "G#5", 80 },
	{ "A5", 81 },
	{ "Bb5", 82 },
	{ "B5", 83 },
	{ "C6", 84 },
	{ "C#6", 85 },
	{ "D6", 86 },
	{ "Eb6", 87 },
	{ "E6", 88 },
	{ "F6", 89 },
	{ "F#6", 90 },
	{ "G6", 91 },
	{ "G#6", 92 },
	{ "A6", 93 },
	{ "Bb6", 94 },
	{ "B6", 95 },
	{ "C7", 96 },
	{ "C#7", 97 },
	{ "D7", 98 },
	{ "Eb7", 99 },
	{ "E7", 100 },
	{ "F7", 101 },
	{ "F#7", 102 },
	{ "G7", 103 },
	{ "G#7", 104 },
	{ "A7", 105 },
	{ "Bb7", 106 },
	{ "B7", 107 },
	{ "C8", 108 },
	{ "C#8", 109 },
	{ "D8", 110 },
	{ "Eb8", 111 },
	{ "E8", 112 },
	{ "F8", 113 },
	{ "F#8", 114 },
	{ "G8", 115 },
	{ "G#8", 116 },
	{ "A8", 117 },
	{ "Bb8", 118 },
	{ "B8", 119 },
	{ "blank", 0 }
};

MIDI::MIDI(MIDITrack * track, std::wstring fileName ) {
	this->fileName = fileName;
	this->track = track;
}


bool MIDI::sortReleaseKeys(std::pair<int, std::pair<int64_t, TrackNote *> *> * i, std::pair<int, std::pair<int64_t, TrackNote *> *> * j) {
	return i->second->first + i->second->second->getLength() < j->second->first + j->second->second->getLength();
};

void MIDI::save() {
	jdksmidi::MIDITimedBigMessage m; // the object for individual midi events
	unsigned char chan, // internal midi channel number 0...15 (named 1...16)
		note, velocity, ctrl, val;

	jdksmidi::MIDIClockTime t; // time in midi ticks
	jdksmidi::MIDIClockTime dt = 1000; // time interval (1 second)
	//ms ticks
	int clks_per_beat = 1000; // number of ticks in crotchet (1...32767)
	int bpmTempo = track->getTempo();
	int quarterNoteMicroSeconds = 60000000 / (bpmTempo ? bpmTempo : 120);
	int num_tracks = 1; // tracks 0 and 1
	unsigned int channels = 0;

// we change panorama in channels 0-2
	int64_t currTime = 0;

	std::map<std::string, int> melodyTrackMap;
	std::map<int, int> melodyInstrumentChannelMap;
	std::map<int, int> melodyChannelInstrumentMap;

	auto * notesMap = track->getTrackMap();
	for (auto it = notesMap->begin(); it != notesMap->end(); ++it) {
		for (auto nit = it->second->begin(); nit != it->second->end(); ++nit) {
			for (auto thisNote : *((*nit)->getAllNotes())) {
				if (melodyTrackMap.find(thisNote->getMelodyGroup()) == melodyTrackMap.end()) {
					melodyTrackMap.insert_or_assign(thisNote->getMelodyGroup(), num_tracks++);
				}

				if (melodyInstrumentChannelMap.find(thisNote->getInstrument()) == melodyInstrumentChannelMap.end()) {
					melodyChannelInstrumentMap.insert_or_assign(channels, thisNote->getInstrument());
					melodyInstrumentChannelMap.insert_or_assign(thisNote->getInstrument(), channels++);
				}
			}
		}
	}

	jdksmidi::MIDIMultiTrack tracks(num_tracks);  // the object which will hold all the tracks
	tracks.SetClksPerBeat(clks_per_beat);
	int trk; // track number, 0 or 1

	t = 0;
	m.SetTime(t);

	// track 0 is used for tempo and time signature info, and some other stuff
	trk = 0;
	m.SetTimeSig(4, 2); // measure 4/4 (default values for time signature)
	tracks.GetTrack(trk)->PutEvent(m);

	int tempo = 60000000/(bpmTempo?bpmTempo:120); // set tempo to 1 000 000 usec = 1 sec in crotchet
						 // with value of clks_per_beat (100) result 10 msec in 1 midi tick
						 // If no tempo is define, 120 beats per minute is assumed.

						 // m.SetTime( t ); // do'nt need, because previous time is not changed
	m.SetTempo(tempo);
	tracks.GetTrack(trk)->PutEvent(m);

	// META_TRACK_NAME text in track 0 music notation software like Sibelius uses as headline of the music
	tracks.GetTrack(trk)->PutTextEvent(t, jdksmidi::META_TRACK_NAME, track->getName().c_str());

	// create cannal midi events and add them to a track 1
	for (auto track : melodyTrackMap) {
		trk = track.second;
		// META_TRACK_NAME text in tracks >= 1 Sibelius uses as instrument name (left of staves)
		tracks.GetTrack(trk)->PutTextEvent(t, jdksmidi::META_TRACK_NAME, track.first.c_str());

		for (unsigned i = 0; i < channels; i++) {
			m.SetControlChange(chan = i, ctrl = 0xA, 64); // channel 0 panorama = 0 at the left
			tracks.GetTrack(trk)->PutEvent(m);
		}

		// we change musical instrument in channels 0-2
		for (unsigned i = 0; i < channels; i++) {
			//GeneratorLog::LogMsg(L"Instrument:" + std::to_wstring(melodyChannelInstrumentMap[i] - 1) + L" on track: " + std::to_wstring(trk));
			m.SetProgramChange(chan = i, val = melodyChannelInstrumentMap[i]-1); // channel 0 instrument 19 - Church Organ
			tracks.GetTrack(trk)->PutEvent(m);
		}
	}

	// create individual midi events with the MIDITimedBigMessage and add them to a track 1
	t = 0;

	// we add note 1: press and release in (dt) ticks
	for (auto track : melodyTrackMap) {
		int64_t maxRelease = 0;
		std::vector<std::pair<int, std::pair<int64_t, TrackNote *> *> *> waitingForRelease;
		for (auto it = notesMap->begin(); it != notesMap->end(); ++it) {
			currTime = it->first;
			for (auto cit = waitingForRelease.begin(); cit != waitingForRelease.end();) {
				if ((*cit)->second->second->getLength() + (*cit)->second->first <= currTime) {
					m.SetTime((jdksmidi::MIDIClockTime)(((((double)(*cit)->second->first + (double)(*cit)->second->second->getLength()) / (double)quarterNoteMicroSeconds) * 1000.0) - 1));
					m.SetNoteOff((*cit)->first, MIDI::noteNumbers[(*cit)->second->second->getNote()], velocity);
					// alternative form of note off event: useful to reduce midifile size if running status is used (on default so)
					// m.SetNoteOn( chan, note, 0 );

					//GeneratorLog::LogMsg(L"NOTE OFF:" + std::to_wstring(MIDI::noteNumbers[(*cit)->second->second->getNote()]) + L" TRK: " + std::to_wstring(melodyTrackMap.at((*cit)->second->second->getMelodyGroup())) + L" MLDY GRP: " + GetWC((*cit)->second->second->getMelodyGroup().c_str()));
					tracks.GetTrack(melodyTrackMap.at((*cit)->second->second->getMelodyGroup()))->PutEvent(m);

					auto toDelete = *cit;
					waitingForRelease.erase(cit);
					delete toDelete->second;
					delete toDelete;
					cit = waitingForRelease.begin();
				} else {
					++cit;
				}
			}

			for (auto nit = it->second->begin(); nit != it->second->end(); ++nit) {
				for (auto thisNote : *((*nit)->getAllNotes())) {
					if (track.first == (*nit)->getMelodyGroup()) {
						m.SetTime((int)((((double)currTime / (double)quarterNoteMicroSeconds)) * 1000.0));
						chan = melodyInstrumentChannelMap[thisNote->getInstrument()];
						m.SetNoteOn(chan, note = MIDI::noteNumbers[thisNote->getNote()], velocity = 100);

						//GeneratorLog::LogMsg(L"NOTE ON:" + std::to_wstring(MIDI::noteNumbers[(*nit)->getNote()]) + L" TRK: " + std::to_wstring(melodyTrackMap.at((*nit)->getMelodyGroup())) + L" MLDY GRP: " + GetWC((*nit)->getMelodyGroup().c_str()));
						tracks.GetTrack(melodyTrackMap.at(thisNote->getMelodyGroup()))->PutEvent(m);

						waitingForRelease.push_back(new std::pair<int, std::pair<int64_t, TrackNote *> *>(
							chan,
							new std::pair<int64_t, TrackNote *>(currTime, thisNote)
							));
						maxRelease = currTime + thisNote->getLength() > maxRelease ? currTime + thisNote->getLength() : maxRelease;
					}
				}
			}
		}
		std::sort(waitingForRelease.begin(), waitingForRelease.end(), MIDI::sortReleaseKeys);
		for (auto cit = waitingForRelease.begin(); cit != waitingForRelease.end();) {
			m.SetTime((jdksmidi::MIDIClockTime)((((((double)(*cit)->second->first + (double)(*cit)->second->second->getLength()) / (double)quarterNoteMicroSeconds)) * 1000.0) - 1));
			m.SetNoteOff((*cit)->first, MIDI::noteNumbers[(*cit)->second->second->getNote()], velocity);


			//GeneratorLog::LogMsg(L"NOTE OFF:" + std::to_wstring(MIDI::noteNumbers[(*cit)->second->second->getNote()]) + L" TRK: " + std::to_wstring(melodyTrackMap.at((*cit)->second->second->getMelodyGroup())) + L" MLDY GRP: " + GetWC((*cit)->second->second->getMelodyGroup().c_str()));
			tracks.GetTrack(melodyTrackMap.at((*cit)->second->second->getMelodyGroup()))->PutEvent(m);

			auto toDelete = *cit;
			waitingForRelease.erase(cit);
			delete toDelete->second;
			delete toDelete;
			cit = waitingForRelease.begin();
		}
	}

	// if events in any track recorded not in order of the growth of time,
	// tracks.SortEventsOrder(); // it is necessary to do this before write step

	// to write the multi track object out, you need to create an output stream for the output filename
	if (boost::filesystem::exists(fileName + L"Track.mid")) {
		int i = 0;
		do {
			i++;
		} while (boost::filesystem::exists(fileName + std::to_wstring(i) + L"Track.mid"));
		fileName = fileName + std::to_wstring(i) + L"Track.mid";
	} else {
		fileName = fileName + L"Track.mid";
	}

	const wchar_t *outfile_name = fileName.c_str();

	jdksmidi::MIDIFileWriteStreamFileName out_stream(outfile_name);

	// then output the stream like my example does, except setting num_tracks to match your data

	if (out_stream.IsValid()) {
		// the object which takes the midi tracks and writes the midifile to the output stream
		jdksmidi::MIDIFileWriteMultiTrack writer(&tracks, &out_stream);

		// write the output file
		if (writer.Write(num_tracks)) {
			std::cout << "\nOK writing file " << outfile_name << std::endl;
		} else {
			std::cerr << "\nError writing file " << outfile_name << std::endl;
		}
	} else {
		std::cerr << "\nError opening file " << outfile_name << std::endl;
	}
}
