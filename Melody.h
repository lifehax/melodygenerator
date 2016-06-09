#pragma once

#include <boost/variant.hpp>
#include <boost/function.hpp>
#include <vector>
#include <map>
#include <string>
#include <sstream>
#include <functional>
#include <iostream>
#include "TrackNote.h"
#include "MIDITrack.h"
#include "Harmony.h"
#include "MelodyParameter.h"

class Melody {
protected:
	static int NumberOfMelodies;
	std::string uniqueKey;
	MIDITrack * forTrack;
	std::map<MelodyParameterType, void *> parameters;

public:
	Melody(MIDITrack *);
	int limitNote(int);
	std::string getUniqueName();
	MIDITrack * getTrack();

	template <typename ParameterType>
	MelodyParameter<ParameterType> * setParam(MelodyParameterType parameter, ParameterType value) {
		MelodyParameter<ParameterType> * obj;
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			obj = (MelodyParameter<ParameterType> *)(ret->second);
			obj->setParameterValue(value);
		} else {
			obj = new MelodyParameter<ParameterType>(
				MelodyParameterID::NextParamIdentifier(),
				parameter,
				value
			);
			this->parameters.insert_or_assign(parameter, obj);
		}
		return obj;
	}

	template <typename ParameterType>
	ParameterType getParam(MelodyParameterType parameter) {
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			MelodyParameter<ParameterType> * obj = (MelodyParameter<ParameterType> *)(ret->second);
			return obj->getParameterValue();
		} else {
			std::cerr << "Param Not Set: " << MelodyParameterTypeStrMap[parameter] << std::endl;
			throw "Param Not Set";
		}
	}

	template <typename ParameterType>
	ParameterType getParamDefault(MelodyParameterType parameter, ParameterType defaultValue) {
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			MelodyParameter<ParameterType> * obj = (MelodyParameter<ParameterType> *)(ret->second);
			return obj->getParameterValue();
		} else {
			return defaultValue;
		}
	}

	template <typename ParameterType>
	ParameterType getParamDefaultFunc(MelodyParameterType parameter, std::function<ParameterType(Melody *)> defaultValueFunc) {
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			MelodyParameter<ParameterType> * obj = (MelodyParameter<ParameterType> *)(ret->second);
			return obj->getParameterValue();
		} else {
			return defaultValueFunc(this);
		}
	}

	std::string getParamID(MelodyParameterType parameter) {
		auto ret = this->parameters.find(parameter);
		if (ret != this->parameters.end()) {
			MelodyParameter<void *> * obj = (MelodyParameter<void *> *)(ret->second);
			return obj->getID();
		} else {
			throw "Param Not Set";
		}
	}

	Melody * setParamTypeless(MelodyParameterType type, void * value) {
		this->parameters.insert_or_assign(type, value);
		return this;
	}
};
