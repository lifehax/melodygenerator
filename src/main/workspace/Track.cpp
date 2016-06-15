#include "stdafx.h"
#include "Track.h"

Track::Track() {
}

void Track::setName(std::string name) {
	this->name = name;
}

std::string Track::getName() {
	return name;
}