#include "stdafx.h"

#include <functional>
#include <thread>

#include "Type.h"
#include "MusicGeneratorApp.h"
#include "MainWindow.h"
#include "MainTabs.h"
#include "LogTab.h"
#include "EventHandler.h"
#include "PresetGeneratorTask.h"

LogTab::LogTab(MainTabs * mainTabs) : Tab(mainTabs) {
}

void LogTab::init() {
	RECT tabBoxCoords;

	GetClientRect(this->tabs->getTabs(), &tabBoxCoords);
	TabCtrl_AdjustRect(this->tabs->getTabs(), false, &tabBoxCoords);

	int tabWidth = (tabBoxCoords.right - tabBoxCoords.left);
	int tabHeight = (tabBoxCoords.bottom - tabBoxCoords.top);

	int logContainerWidth = tabWidth - 100;
	int logContainerTop = 50;
	int logContainerLeft = 50;
	int logContainerHeight = tabHeight - 100;

	this->generateLog = CreateWindowW(L"EDIT", NULL, WS_CHILD | WS_VSCROLL | ES_LEFT | ES_MULTILINE | ES_AUTOVSCROLL |
		ES_READONLY | WS_HSCROLL | ES_AUTOHSCROLL,
		logContainerLeft, logContainerTop, logContainerWidth, logContainerHeight, this->tabs->getWindow()->getWindow(),
		(HMENU)ID_PRESETGENLOGBOX, musicGeneratorApp.getInstance(), NULL);

	GeneratorLog::RegisterListener(std::bind(&LogTab::logListen, this, std::placeholders::_1));

}

void LogTab::logListen(std::wstring msg) {
	std::wstring textBoxText;

	int sizeOfLog = Edit_GetTextLength(this->generateLog);
	if (sizeOfLog > 0) {
		wchar_t * logText = new wchar_t[sizeOfLog + 1];
		Edit_GetText(this->generateLog, logText, sizeOfLog);

		textBoxText.append(logText);
		textBoxText.append(L"\r\n");
	}
	int position = textBoxText.length();
	textBoxText.append(msg);

	Edit_SetText(this->generateLog, textBoxText.c_str());
	Edit_SetSel(this->generateLog, position, position);
}

void LogTab::show() {
	ShowWindow(this->generateLog, SW_SHOW);
}

void LogTab::hide() {
	ShowWindow(this->generateLog, SW_HIDE);
}

void LogTab::resize() {
	RECT tabBoxCoords;

	GetClientRect(this->tabs->getTabs(), &tabBoxCoords);
	TabCtrl_AdjustRect(this->tabs->getTabs(), false, &tabBoxCoords);

	int tabWidth = (tabBoxCoords.right - tabBoxCoords.left);
	int tabHeight = (tabBoxCoords.bottom - tabBoxCoords.top);

	int logContainerWidth = tabWidth - 100;
	int logContainerTop = 50;
	int logContainerLeft = 50;
	int logContainerHeight = tabHeight - 100;

	SetWindowPos(this->generateLog, NULL, logContainerLeft, logContainerTop, logContainerWidth, logContainerHeight, NULL);
}

std::wstring LogTab::getName() {
	return L"Generator Log";
}
