#pragma once

#include "stdafx.h"
#include <string>
#include <map>
#include <vector>

class PresetGeneratorOptions;

class TrackOptionItem {
protected:
	PresetGeneratorOptions * options;
	bool shown;
	bool required;
	int x;
	int y;
	HWND label;
	std::map<std::string, std::string> subOptionsMap;

public:
	TrackOptionItem(PresetGeneratorOptions *, std::map<std::string, std::string>);

	virtual void setShown(bool);
	virtual bool getShown();
	
	virtual bool getRequired();
	virtual void setRequired(bool);

	virtual int getX();
	virtual void setX(int);
	virtual int getY();
	virtual void setY(int);

	virtual int getHeight() = 0;
	virtual int getWidth() = 0;

	virtual void init();
	virtual void show();
	virtual void hide();
	virtual void resize();

	virtual void initChild() = 0;
	virtual void showChild() = 0;
	virtual void hideChild() = 0;
	virtual void resizeChild() = 0;

	virtual std::string getValue();
	virtual std::string getValueChild() = 0;
	virtual std::string getType() = 0;
	virtual std::wstring getLabel() = 0;

	static const std::vector<std::string> list;
	static std::map<std::string, TrackOptionItem *(*)(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap)> classMap;
	static TrackOptionItem * CreateFromName(std::string name, PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap);
};

template<typename T> TrackOptionItem * createTrackOptionItemFactory(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) {
	return (TrackOptionItem *)new T(options, subOptionsMap);
}

