#include "stdafx.h"

#include "Melody.h"
#include "Harmony.h"
#include "TrackBoardMelodyParams.h"
#include "TrackBoard.h"

TrackBoardMelodyParams::TrackBoardMelodyParams(TrackBoard * board) {
}


void TrackBoardMelodyParams::copyTo(TrackBoardMelodyParams * params) {
	params->setParams(&this->parameters);
}

void TrackBoardMelodyParams::setParams(std::map<MelodyParameterType, std::pair<TrackBoardMelodyParameterType, void *> *> * params) {
	for (auto param : *params) {
		this->parameters.insert_or_assign(param.first, param.second);
	}
}

void TrackBoardMelodyParams::addToMelody(Melody * melody, std::map<MelodyParameterType, std::string> * paramVariations) {
	std::vector<TrackBoardSubParam * > * subParams = new std::vector<TrackBoardSubParam * >();

	for (auto param : this->parameters) {
		if (param.second->first == TrackBoardMelodyParameterType::RANDOM) {
			melody->setParamTypeless(param.first, ((TrackBoardParamRandomize *)param.second->second)->getValue());
		} else if (param.second->first == TrackBoardMelodyParameterType::VARIATION) {
			TrackBoardParamVariation * variations = ((TrackBoardParamVariation *)param.second->second);
			if (paramVariations == NULL) {
				melody->setParamTypeless(param.first, variations->getVariation(variations->getDefault()));
			} else {
				auto variation = paramVariations->find(param.first);
				if (variation == paramVariations->end()) {
					melody->setParamTypeless(param.first, variations->getVariation(variations->getDefault()));
				} else {
					melody->setParamTypeless(param.first, variations->getVariation(variation->second));
				}
			}
		} else if (param.second->first == TrackBoardMelodyParameterType::SUB) {
			subParams->push_back((TrackBoardSubParam *)param.second->second);
		} else {
			melody->setParamTypeless(param.first, param.second->second);
		}
	}

	for (auto subParam : *subParams) {
		std::string paramID = melody->getParamID(subParam->getOtherType());
		melody->setParamTypeless(subParam->getParamType(), subParam->getValue(paramID));
	}
}
