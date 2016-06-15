#include "stdafx.h"
#include <map>
#include "RandomRhythmGenerator.h"

RandomRhythmGenerator::RandomRhythmGenerator(double notesPerBar, int noteDivision) : RhythmGenerator(notesPerBar, noteDivision) {
}

std::vector<float> * RandomRhythmGenerator::getRhythm() {
	std::vector<float> * notesOut = new std::vector<float>();
	std::vector<float> notes({
		0.25, 0.5, 1, 2
	});
	std::map<float, int> noteLengthWeight;
	int totalWeight = 0;
	for (size_t i = 0; i < notes.size(); i++) {
		noteLengthWeight[notes[i]] = (rand() % 4) + 1;
		totalWeight += noteLengthWeight[notes[i]];
	}

	int size = (rand() % 3) + 1;
	for (int i = 0; i < size; i++) {
		double thisBarLength = 0;
		double noteDivisionFactor = 4.0 / this->noteDivision;

		while (thisBarLength < this->notesPerBar) {
			int totalWeight = 0;
			std::vector<float> notes;
			for (auto note : noteLengthWeight) {
				if (note.first + thisBarLength <= (this->notesPerBar * noteDivisionFactor)) {
					notes.push_back(note.first);
					totalWeight += note.second;
				}
			}

			if (totalWeight == 0) {
				float note = ((float)this->notesPerBar * (float)noteDivisionFactor) - (float)thisBarLength;
				noteLengthWeight[note] = 1;
				notes.push_back(note);
				totalWeight += 1;
			}

			int pick = rand() % totalWeight;
			int weight = 0;
			for (auto note : notes) {
				if (weight <= pick && pick < weight + noteLengthWeight[note]) {
					notesOut->push_back(note);
					thisBarLength += note;
					break;
				}
				weight += noteLengthWeight[note];
			}
		}
	}

	for (int i = 0; i < size; i++) {
		int pick = rand() % totalWeight;
		int weight = 0;
		for (auto note : notes) {
			if (weight <= pick && pick < weight + noteLengthWeight[note]) {
				notesOut->push_back(note);
			}
			weight += noteLengthWeight[note];
		}
	}
	return notesOut;
}
