#include "stdafx.h"
#include "TrackBoardMelody.h"
#include "TrackBoardMelodyParams.h"
#include "TrackBoardMelodyType.h"

TrackBoardMelody::TrackBoardMelody(TrackBoard * board, TrackBoardMelodyParams * params) {
	this->board = board;
	this->params = new TrackBoardMelodyParams(board);
	params->copyTo(this->params);
}

