#pragma once

#include "stdafx.h"
#include "TrackOptionItem.h"
#include <string>
#include <map>

class ComboBoxOption : public TrackOptionItem {
protected:
	std::map<int, std::pair<std::string, std::string>> * optionsMap;
	HWND listBox;

public:
	ComboBoxOption(PresetGeneratorOptions *, std::map<std::string, std::string>);

	virtual int getHeight();
	virtual int getWidth();

	virtual void initChild();
	virtual void showChild();
	virtual void hideChild();
	virtual void resizeChild();
	virtual std::string getValueChild();

	virtual std::string getType() = 0;
	virtual std::map<std::string, std::string> * getOptions() = 0;
};