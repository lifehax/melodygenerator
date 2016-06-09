#include "stdafx.h"
#include "TrackBoardParamRandomize.h"

#include <map>

template<class ParameterType>
TrackBoardParamRandomize<ParameterType>::TrackBoardParamRandomize(TrackBoardParams * params, MelodyParameterType parameter) {
	this->params = params;
	this->parameter = parameter;
}

template<class ParameterType>
void * TrackBoardParamRandomize<ParameterType>::getValue() {

}
