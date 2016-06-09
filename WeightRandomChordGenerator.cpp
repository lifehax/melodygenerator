#include "stdafx.h"

#include "Chord.h"
#include "WeightRandomChordGenerator.h"

WeightRandomChordGenerator::WeightRandomChordGenerator(int size) {
	this->scale = NULL;
	this->size = size;
}

void WeightRandomChordGenerator::setScale(Scale * scale) {
	this->scale = scale;
}

std::vector<std::string> * WeightRandomChordGenerator::getChordPattern() {
	std::vector<std::string> * outChords = new std::vector<std::string>();
	std::vector<std::string> * possibleChords = new std::vector<std::string>();
	if (scale == NULL) {
		possibleChords = &Chord::Chords;
	} else {
		possibleChords = Chord::ChordsInScale(scale);
	}
	for (int i = 0; i < this->size; i++) {
		outChords->push_back(possibleChords->at(rand() % possibleChords->size()));
	}
	return outChords;
}
