#pragma once

#include <vector>

class TrackBoardMelodyParams;
#include "MelodyParameter.h"

class TrackBoardParamRandomize {
protected:
	TrackBoardMelodyParams * params;
	MelodyParameterType parameter;
	std::vector<std::pair<void *, int> *> * options;

public:
	TrackBoardParamRandomize(TrackBoardMelodyParams * params, MelodyParameterType parameter) {
		this->params = params;
		this->parameter = parameter;
		this->options = new std::vector<std::pair<void *, int> *>();
	}

	template<typename ParameterType>
	MelodyParameter<ParameterType> * addParam(ParameterType value, int weight) {
		MelodyParameter<ParameterType> * newValue = new MelodyParameter<ParameterType>(
			MelodyParameterID::NextParamIdentifier(), parameter, value
		);
		this->options->push_back(
			new std::pair<void *, int>(
				newValue,
				weight
			)
		);
		return newValue;
	}

	TrackBoardMelodyParams * getParams() {
		return this->params;
	}

	void * getValue() {
		int totalWeight = 0;

		for (auto val : *this->options) {
			totalWeight += val->second;
		}

		int pick = rand() % (totalWeight);
		totalWeight = 0;
		for (auto val : *this->options) {
			if (totalWeight <= pick && pick < totalWeight + val->second) {
				return val->first;
			}
			totalWeight += val->second;
		}

		return NULL;
	}
};
