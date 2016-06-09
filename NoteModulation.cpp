#include "stdafx.h"

#include "Track.h"
#include "ModularMelody.h"
#include "NoteModulation.h"

NoteModulation::NoteModulation(ModularMelody * melody) {
	this->forTrack = melody->getTrack();
	this->forMelody = melody;
}
