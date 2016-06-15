#pragma once

#include <typeinfo>
#include "Melody.h"
#include "MelodyParameter.h"

class TrackBoard;
class Harmony;
class TrackBoardMelody;

#include "TrackBoardParamRandomize.h"
#include "TrackBoardParamVariation.h"
#include "TrackBoardSubParam.h"

enum class TrackBoardMelodyParameterType {
	RANDOM,
	VARIATION,
	DIRECT,
	SUB
};

class TrackBoardMelodyParams {
protected:
	std::map<MelodyParameterType, std::pair<TrackBoardMelodyParameterType, void *> *> parameters;

public:
	TrackBoardMelodyParams(TrackBoard *);

	TrackBoardMelodyParams * setHarmony(Harmony *);
	Harmony * getHarmony();

	template <typename ParameterType>
	MelodyParameter<ParameterType> * setParam(MelodyParameterType parameter, ParameterType value) {
		MelodyParameter<ParameterType> * obj;
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			obj = (MelodyParameter<ParameterType> *)(ret->second->second);
			obj->setParameterValue(value);
		} else {
			obj = new MelodyParameter<ParameterType>(
				MelodyParameterID::NextParamIdentifier(), parameter, value
			);
			this->parameters.insert_or_assign(parameter,
				new std::pair<TrackBoardMelodyParameterType, void *>(
					TrackBoardMelodyParameterType::DIRECT,
					obj
				)
			);
		}
		return obj;
	}

	TrackBoardParamRandomize * setRandomParam(MelodyParameterType parameter) {
		TrackBoardParamRandomize * newValue = new TrackBoardParamRandomize(this, parameter);
		this->parameters.insert_or_assign(parameter,
			new std::pair<TrackBoardMelodyParameterType, void *>(
				TrackBoardMelodyParameterType::RANDOM,
				newValue
			)
		);
		return newValue;
	}

	TrackBoardParamVariation * setVariationParam(MelodyParameterType parameter) {
		TrackBoardParamVariation * newValue = new TrackBoardParamVariation(this, parameter);
		this->parameters.insert_or_assign(parameter,
			new std::pair<TrackBoardMelodyParameterType, void *>(
				TrackBoardMelodyParameterType::VARIATION,
				newValue
			)
		);
		return newValue;
	}

	TrackBoardSubParam * setSubParam(MelodyParameterType parameter, MelodyParameterType other) {
		TrackBoardSubParam * newValue = new TrackBoardSubParam(this, parameter, other);
		this->parameters.insert_or_assign(parameter,
			new std::pair<TrackBoardMelodyParameterType, void *>(
				TrackBoardMelodyParameterType::SUB,
				newValue
			)
		);
		return newValue;
	}

	template <typename ParameterType>
	ParameterType getParam(MelodyParameterType parameter) {
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			MelodyParameter<ParameterType> * obj = (MelodyParameter<ParameterType> *)(ret->second->second);
			return obj->getParameterValue();
		} else {
			throw "Param Not Set";
		}
	}

	void copyTo(TrackBoardMelodyParams * params);
	void addToMelody(Melody * melody, std::map<MelodyParameterType, std::string> * paramVariations);
	void setParams(std::map<MelodyParameterType, std::pair<TrackBoardMelodyParameterType, void *> *> *);
};

