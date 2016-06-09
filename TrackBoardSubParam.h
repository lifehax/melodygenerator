#pragma once

#include <map>
#include <vector>

class TrackBoardMelodyParams;
#include "MelodyParameter.h"

class TrackBoardSubParam {
protected:
	TrackBoardMelodyParams * params;
	MelodyParameterType parameter;
	MelodyParameterType otherType;
	std::map<std::string, void *> * options;

public:
	TrackBoardSubParam(TrackBoardMelodyParams * params, MelodyParameterType parameter, MelodyParameterType otherParameter) {
		this->params = params;
		this->parameter = parameter;
		this->otherType = otherParameter;
		this->options = new std::map<std::string, void *>();
	}

	template <typename ParameterType>
	MelodyParameter<ParameterType> * addParam(std::string otherID, ParameterType value) {
		MelodyParameter<ParameterType> * newValue = new MelodyParameter<ParameterType>(MelodyParameterID::NextParamIdentifier(), this->parameter, value);
		this->options->insert_or_assign(
			otherID,
			newValue
		);
		return newValue;
	}

	MelodyParameterType getParamType() {
		return this->parameter;
	}

	MelodyParameterType getOtherType() {
		return this->otherType;
	}

	TrackBoardMelodyParams * getParams() {
		return this->params;
	}

	void * getValue(std::string otherPick) {
		return this->options->at(otherPick);
	}
};
