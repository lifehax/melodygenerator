#include "stdafx.h"
#include "RandomPatternGenerator.h"

std::vector<int> * RandomPatternGenerator::getPattern() {
	std::vector<int> * pattern = new std::vector<int>();

	int size = (rand() % 7) + 4;
	for (int i = 0; i < size; i++) {
		int dir = rand() % 2 == 1 ? -1 : 1;
		pattern->push_back(dir * ((rand() % 5) + 1));
	}

	return pattern;
}

