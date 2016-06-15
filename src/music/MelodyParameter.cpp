#include "stdafx.h"
#include "MelodyParameter.h"

int MelodyParameterID::currentParamIdentifier = 0;

std::map<MelodyParameterType, std::string> MelodyParameterTypeStrMap = {
	{ MelodyParameterType::PRIORITY, "Priority" },
	{ MelodyParameterType::NOTE_LENGTH, "NoteLength" },
	{ MelodyParameterType::SONG_LENGTH, "SongLength" },
	{ MelodyParameterType::MODULATOR, "Modulator" },
	{ MelodyParameterType::ROOT_NOTE, "RootNote" },
	{ MelodyParameterType::LENGTH, "Length" },
	{ MelodyParameterType::SIZE, "Size" },
	{ MelodyParameterType::TRACK_TIME, "TrackTime" },
	{ MelodyParameterType::SCALE, "Scale" },
	{ MelodyParameterType::SCALE_MODE, "ScaleMode" },
	{ MelodyParameterType::RHYTHM, "Rhythm" },
	{ MelodyParameterType::MODULATION_FUNCTION, "ModulationFunction" },
	{ MelodyParameterType::HARMONIZER, "Harmonizer" },
	{ MelodyParameterType::UPPER_NOTE_LIMIT, "UpperNoteLimit" },
	{ MelodyParameterType::LOWER_NOTE_LIMIT, "LowerNoteLimit" },
	{ MelodyParameterType::MELODY_REPEAT_SIZE, "MelodyRepeatSize" }
};
