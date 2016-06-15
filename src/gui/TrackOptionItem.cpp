#include "stdafx.h"

#include "MusicGeneratorApp.h"
#include "PresetGeneratorOptions.h"
#include "TrackOptionItem.h"
#include "InstrumentListOption.h"
#include "TimeSignatureOption.h"


const std::vector<std::string>  TrackOptionItem::list = {
	"InstrumentList",
	"TimeSignature"
};

std::map<std::string, TrackOptionItem *(*)(PresetGeneratorOptions *, std::map<std::string, std::string>)> TrackOptionItem::classMap({
	{ "InstrumentList", &createTrackOptionItemFactory<InstrumentListOption> },
	{ "TimeSignature", &createTrackOptionItemFactory<TimeSignatureOption> }
});


TrackOptionItem * TrackOptionItem::CreateFromName(std::string name, PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) {
	return TrackOptionItem::classMap[name](options, subOptionsMap);
}

TrackOptionItem::TrackOptionItem(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) {
	this->options = options;
	this->subOptionsMap = subOptionsMap;
	this->required = true;
}

bool TrackOptionItem::getRequired() {
	return this->required;
}

void TrackOptionItem::setRequired(bool required) {
	this->required = required;
}

void TrackOptionItem::setShown(bool shown) {
	this->shown = shown;
}

bool TrackOptionItem::getShown() {
	return this->shown;
}

int TrackOptionItem::getX() {
	return this->x;
}

void TrackOptionItem::setX(int x) {
	this->x = x;
}

int TrackOptionItem::getY() {
	return this->y;
}

void TrackOptionItem::setY(int y) {
	this->y = y;
}

std::string TrackOptionItem::getValue() {
	std::string value = this->getValueChild();
	return value;
}

void TrackOptionItem::init() {
	this->label = CreateWindow(WC_STATIC, this->getLabel().c_str(), WS_CHILD | SS_LEFT, this->getX(), this->getY(), 150, 30,
		this->options->getOptionArea(), (HMENU)9009, musicGeneratorApp.getInstance(), NULL);
	this->initChild();
}

void TrackOptionItem::show() {
	ShowWindow(this->label, SW_SHOW);
	this->showChild();
}

void TrackOptionItem::hide() {
	ShowWindow(this->label, SW_HIDE);
	this->hideChild();
}

void TrackOptionItem::resize() {
	SetWindowPos(this->label, NULL, this->getX(), this->getY(), 150, 30, NULL);
	this->resizeChild();
}

