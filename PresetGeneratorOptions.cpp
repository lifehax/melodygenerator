#include "stdafx.h"

#include "MusicGeneratorApp.h"
#include "MainTabs.h"
#include "MainWindow.h"
#include "PresetGeneratorOptions.h"
#include "PresetGeneratorTab.h"
#include "Type.h"
#include "TrackOptionItem.h"

PresetGeneratorOptions::PresetGeneratorOptions(PresetGeneratorTab * tab, MainWindow * mainWindow) {
	this->tab = tab;
	this->mainWindow = mainWindow;
	this->controls = new std::map<int, std::map<std::string, TrackOptionItem *> *>();
}

void PresetGeneratorOptions::init() {
	RECT tabBoxCoords;

	GetClientRect(this->tab->getTabs()->getTabs(), &tabBoxCoords);
	TabCtrl_AdjustRect(this->tab->getTabs()->getTabs(), false, &tabBoxCoords);

	int tabWidth = (tabBoxCoords.right - tabBoxCoords.left);
	int tabHeight = (tabBoxCoords.bottom - tabBoxCoords.top);

	WNDCLASS wc;
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = MainWindow::Proc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = sizeof(long);
	wc.hInstance = musicGeneratorApp.getInstance();
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = L"GeneratorOptionsArea";

	RegisterClass(&wc);

	int listWidth = (int)(tabWidth * 0.25);
	int optionAreaWidth = (tabWidth - (listWidth)) - 40;
	int optionAreaHeight = tabHeight - 160;
	int optionAreaTop = tabBoxCoords.top + 20;
	int optionAreaLeft = (int)(listWidth + 20);

	this->optionArea = CreateWindowExW(NULL, L"GeneratorOptionsArea", (LPCTSTR)NULL, WS_CHILD | WS_BORDER | WS_VSCROLL,
		optionAreaLeft, optionAreaTop, optionAreaWidth, optionAreaHeight,
		this->mainWindow->getWindow(), (HMENU)ID_GENERATOROPTIONAREA, musicGeneratorApp.getInstance(), NULL);

	this->optionDefaultText = CreateWindowW(WC_STATIC, L"Select Generator Type On Left To Continue...", WS_CHILD | SS_LEFT,
		0, 0, 300, 20,
		this->optionArea, (HMENU)9007, NULL, NULL);

	this->noOptionsText = CreateWindowW(WC_STATIC, L"No Options For Type, Click Generator To Run", WS_CHILD | SS_LEFT,
		0, 0, 300, 20,
		this->optionArea, (HMENU)9008, NULL, NULL);
}

void PresetGeneratorOptions::switchToType(int item) {
	this->currSelection = item;
	if (this->currSelection != LB_ERR) {
		std::map<std::string, TrackOptionItem *> * options = NULL;
		auto optionsIt = this->controls->find(item);
		if (optionsIt == this->controls->end()) {
			Type * type = Type::Create(item);
			std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * typeOptions = type->getOptions();
			if (typeOptions == NULL) {
				ShowWindow(this->optionDefaultText, SW_HIDE);
				ShowWindow(this->noOptionsText, SW_SHOW);
				this->noOptions = true;
			} else {
				std::map<std::string, TrackOptionItem *> * controlsMap =
					new std::map<std::string, TrackOptionItem *>();
				for (auto type : *typeOptions) {
					controlsMap->insert_or_assign(type.first, TrackOptionItem::CreateFromName(
						type.second.first,
						this,
						type.second.second
					));
					controlsMap->at(type.first)->init();
				}
				this->controls->insert_or_assign(item, controlsMap);
				options = controlsMap;
				this->noOptions = false;
			}
		} else {
			options = optionsIt->second;
			this->noOptions = false;
		}
		for (auto checkOptionType : *this->controls) {
			for (auto checkOption : *checkOptionType.second) {
				if (options != NULL && options->find(checkOption.first) != options->end() && checkOptionType.first == this->currSelection) {
					checkOption.second->setShown(true);
				} else {
					checkOption.second->setShown(false);
				}
			}
		}
		this->showHideOptions();
	} else {
		ShowWindow(this->optionDefaultText, SW_SHOW);
		ShowWindow(this->noOptionsText, SW_HIDE);
		this->noOptions = true;
	}
}

void PresetGeneratorOptions::showHideOptions() {
	int currentX = 10;
	int currentY = 0;
	if(!this->noOptions) {
		ShowWindow(this->optionDefaultText, SW_HIDE);
		ShowWindow(this->noOptionsText, SW_HIDE);
	}
	for (auto checkOptionType : *this->controls) {
		for (auto checkOption : *checkOptionType.second) {
			if (checkOption.second->getShown()) {
				checkOption.second->setX(currentX);
				checkOption.second->setY(currentY);
				checkOption.second->resize();
				checkOption.second->show();
				currentY += checkOption.second->getHeight() + 10;
			} else {
				checkOption.second->hide();
			}
		}
	}
}

void PresetGeneratorOptions::show() {
	ShowWindow(this->optionArea, SW_SHOW);
	if (this->currSelection == -1) {
		ShowWindow(this->optionDefaultText, SW_SHOW);
	} else if (this->noOptions) {
		ShowWindow(this->optionDefaultText, SW_HIDE);
		ShowWindow(this->noOptionsText, SW_SHOW);
	} else {
		this->showHideOptions();
	}
}

void PresetGeneratorOptions::hide() {
	ShowWindow(this->optionArea, SW_HIDE);
	ShowWindow(this->optionDefaultText, SW_HIDE);
	ShowWindow(this->noOptionsText, SW_HIDE);
}

void PresetGeneratorOptions::resize() {
	for (auto checkOptionType : *this->controls) {
		for (auto checkOption : *checkOptionType.second) {
			if (checkOption.second->getShown()) {
				checkOption.second->resize();
			}
		}
	}
}

MainWindow * PresetGeneratorOptions::getWindow() {
	return this->mainWindow;
}

HWND PresetGeneratorOptions::getOptionArea() {
	return this->optionArea;
}

bool PresetGeneratorOptions::checkReadyState() {
	for (auto checkOptionType : *this->controls) {
		if (checkOptionType.first == this->currSelection) {
			for (auto checkOption : *checkOptionType.second) {
				if (checkOption.second->getRequired()) {
					if (checkOption.second->getValue() == "") {
						MessageBoxW(this->mainWindow->getWindow(), L"Missing Generator Option Value", NULL, MB_APPLMODAL);
						return false;
					}
				}
			}
		}
	}
	return true;
}

std::map<std::string, std::string> * PresetGeneratorOptions::getOptionValues() {
	std::map<std::string, std::string> * values = new std::map<std::string, std::string>();
	for (auto checkOptionType : *this->controls) {
		if (checkOptionType.first == this->currSelection) {
			for (auto checkOption : *checkOptionType.second) {
				if (checkOption.second->getRequired()) {
					values->insert_or_assign(checkOption.first, checkOption.second->getValue());
				}
			}
		}
	}
	return values;
}
