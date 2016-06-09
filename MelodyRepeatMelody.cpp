#include "stdafx.h"

#include "MelodyRepeatMelody.h"

void MelodyRepeatMelody::addAsPhrase() {

	int noteList = this->forMelody->getParam<int>(MelodyParameterType::ROOT_NOTE);
	ConnectedHarmonyMelody::addAsPhrase();
}
