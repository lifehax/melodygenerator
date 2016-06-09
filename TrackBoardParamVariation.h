#pragma once

#include <map>
#include <string>
#include "MelodyParameter.h"

class TrackBoardMelodyParams;

class TrackBoardParamVariation {

protected:
	TrackBoardMelodyParams * params;
	MelodyParameterType parameter;
	std::string defaultVariation;
	std::map<std::string, void*> * variations;

public:
	TrackBoardParamVariation(TrackBoardMelodyParams * params, MelodyParameterType parameter) {
		this->params = params;
		this->parameter = parameter;
	}

	void setDefault(std::string defaultVariation) {
		this->defaultVariation = defaultVariation;
	}

	std::string getDefault() {
		return this->defaultVariation;
	}

	template <typename ParameterType>
	MelodyParameter<ParameterType> * addVariation(ParameterType value, std::string variation) {
		MelodyParameter<ParameterType> * newValue = new MelodyParameter<ParameterType>(
			MelodyParameterID::NextParamIdentifier(), parameter, value
		);
		this->variations->insert_or_assign(
			variation,
			newValue
		);
		return newValue;
	}

	void * getVariation(std::string variation) {
		return this->variations->at(variation);
	}
};
