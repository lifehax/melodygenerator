#pragma once

#include "NoteModulation.h"
#include "PhraseMelody.h"
#include <map>
#include <vector>

class ModularMelody : public PhraseMelody {
protected:
	std::vector<NoteModulation *> * modulators;

	int waitForNoteTime;
	int64_t waitForNoteBegin;
public:
	ModularMelody(MIDITrack *);

	static const std::vector<std::string> list;
	static std::map<std::string, NoteModulation *(*)(ModularMelody *)> ModularMelody::classMap;
	static NoteModulation * CreateFromName(std::string name);
	static NoteModulation * Create(int);

	void addAsPhrase();
};

template<typename T> NoteModulation * createModulationFactory(ModularMelody * melody) {
	return (NoteModulation *)new T(melody);
}

