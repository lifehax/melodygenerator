#pragma once

#include "ModularMelody.h"
#include <map>
#include <vector>

class ConnectedHarmonyMelody;

class ConnectedMelodies : public std::map<int, ConnectedHarmonyMelody *> {
protected:
public:
	void harmonize();
	void harmonize(std::vector<std::string> *);
};

class ConnectedHarmonyMelody : public ModularMelody {
public:
	enum class HarmonyMode { BY_CALL, AFTER_ADD, NO_HARMONY };

protected:
	ConnectedMelodies * connectedMelodies;

public:
	ConnectedHarmonyMelody(MIDITrack *);

	ConnectedMelodies * getConnections();
	void setConnections(ConnectedMelodies *);
	void linkTo(ConnectedHarmonyMelody *, int);

	void addAsPhrase();
	void harmonize(std::vector<std::string> *);
};

