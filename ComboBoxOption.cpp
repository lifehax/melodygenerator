#include "stdafx.h"

#include "PresetGeneratorOptions.h"
#include "MusicGeneratorApp.h"
#include "TrackOptionItem.h"
#include "InstrumentListOption.h"

ComboBoxOption::ComboBoxOption(PresetGeneratorOptions * options, std::map<std::string, std::string> subOptionsMap) : TrackOptionItem(options, subOptionsMap) {
	this->optionsMap = new std::map<int, std::pair<std::string, std::string>>();
}


std::string ComboBoxOption::getValueChild() {
	int num = ComboBox_GetCurSel(this->listBox);
	return this->optionsMap->find(num) != this->optionsMap->end() ? this->optionsMap->at(num).first : "";
}

void ComboBoxOption::initChild() { 
	this->listBox = CreateWindowW(WC_COMBOBOX, L"ComboSelectBox", WS_CHILD | CBS_DROPDOWN | CBS_HASSTRINGS | WS_OVERLAPPED | WS_VSCROLL,
		this->getX() + 180, this->getY(), CW_USEDEFAULT, CW_USEDEFAULT,
		this->options->getOptionArea(), (HMENU)9010, musicGeneratorApp.getInstance(), NULL);
	std::map<std::string, std::string> * options = this->getOptions();

	SendMessageW(this->listBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(UINT_PTR)L"Select Item...");
	int i = 1;
	for (auto option : *options) {
		this->optionsMap->insert_or_assign(i++, option);
		SendMessageW(this->listBox, (UINT)CB_ADDSTRING, (WPARAM)0, (LPARAM)(UINT_PTR)GetWC(option.second.c_str()));
	}
	SendMessageW(this->listBox, CB_SETCURSEL, (WPARAM)0, (LPARAM)0);
}

int ComboBoxOption::getHeight() {
	return 100;
}

int ComboBoxOption::getWidth() {
	return 580;
}

void ComboBoxOption::showChild() {
	ShowWindow(this->listBox, SW_SHOW);
}

void ComboBoxOption::hideChild() {
	ShowWindow(this->listBox, SW_HIDE);
}

void ComboBoxOption::resizeChild() {
	SetWindowPos(this->listBox, NULL, this->getX() + 180, this->getY(), 400, 500, NULL);
}
