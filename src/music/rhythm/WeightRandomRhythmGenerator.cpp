#include "stdafx.h"
#include <map>
#include "WeightRandomRhythmGenerator.h"

WeightRandomRhythmGenerator::WeightRandomRhythmGenerator(double notesPerBar, int noteDivision) : RhythmGenerator(notesPerBar, noteDivision) {
}

void WeightRandomRhythmGenerator::setWeightMap(std::map<float, int> noteLengthWeight) {
	this->noteLengthWeightMap = noteLengthWeight;
}

std::vector<float> * WeightRandomRhythmGenerator::getRhythm() {
	std::vector<float> * notesOut = new std::vector<float>();
	int size = (rand() % 3) + 1;
	for (int i = 0; i < size; i++) {

		double thisBarLength = 0;
		double noteDivisionFactor = 4.0 / this->noteDivision;

		while(thisBarLength < (this->notesPerBar * noteDivisionFactor)) {
			int totalWeight = 0;
			std::vector<float> notes;
			for (auto note : this->noteLengthWeightMap) {
				if (note.first + thisBarLength <= (this->notesPerBar * noteDivisionFactor)) {
					notes.push_back(note.first);
					totalWeight += note.second;
				}
			}

			if (totalWeight == 0) {
				float note = ((float)this->notesPerBar * (float)noteDivisionFactor) - (float)thisBarLength;
				this->noteLengthWeightMap[note] = 1;
				notes.push_back(note);
				totalWeight += 1;
			}

			int pick = rand() % totalWeight;
			int weight = 0;
			for (auto note : notes) {
				if (weight <= pick && pick < weight + this->noteLengthWeightMap[note]) {
					notesOut->push_back(note);
					thisBarLength += note;
					break;
				}
				weight += this->noteLengthWeightMap[note];
			}
		}

	}
	return notesOut;
}
