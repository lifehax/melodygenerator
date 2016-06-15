#pragma once

#include <map>
#include <vector>
#include <string>
#include <typeinfo>
#include <functional>

class MIDITrack;
class Melody;

template<class MelodyType>
class TrackBoardMelodyType {
protected:
public:
	static MelodyType * Create(MIDITrack * track) {
		return new MelodyType(track);
	}
};

