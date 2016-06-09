#pragma once

class Scale;

class WeightRandomChordGenerator {
protected:
	int size;
	Scale * scale;
public:
	WeightRandomChordGenerator(int);
	void setScale(Scale *);
	std::vector<std::string> * getChordPattern();
};
