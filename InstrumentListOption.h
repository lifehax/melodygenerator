#pragma once

#include "stdafx.h"
#include "ComboBoxOption.h"
#include <string>

class InstrumentListOption : public ComboBoxOption {
protected:
public:
	InstrumentListOption(PresetGeneratorOptions *, std::map<std::string, std::string>);

	virtual std::string getType();
	virtual std::map<std::string, std::string> * getOptions();
	virtual std::wstring getLabel();
};
