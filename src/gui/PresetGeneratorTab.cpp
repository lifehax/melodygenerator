#include "stdafx.h"

#include <functional>
#include <thread>

#include "Type.h"
#include "MusicGeneratorApp.h"
#include "MainWindow.h"
#include "MainTabs.h"
#include "PresetGeneratorTab.h"
#include "EventHandler.h"
#include "PresetGeneratorTask.h"
#include "PresetGeneratorOptions.h"

PresetGeneratorTab::PresetGeneratorTab(MainTabs * mainTabs) : Tab(mainTabs) {
	this->canStartProcess = true;
	this->generatorOptions = new PresetGeneratorOptions(this, this->tabs->getWindow());
}

void PresetGeneratorTab::init() {
	RECT tabBoxCoords;

	GetClientRect(this->tabs->getTabs(), &tabBoxCoords);
	TabCtrl_AdjustRect(this->tabs->getTabs(), false, &tabBoxCoords);

	int tabWidth = (tabBoxCoords.right - tabBoxCoords.left);
	int tabHeight = (tabBoxCoords.bottom - tabBoxCoords.top);

	int listHeaderX = tabBoxCoords.left;
	int listHeaderY = tabBoxCoords.top;

	int listWidth = (int)(tabWidth * 0.25);

	this->listBoxHeader = CreateWindowW(WC_STATIC, L"Select Music Generator Type:",
		WS_CHILD | SS_LEFT,
		listHeaderX, listHeaderY, listWidth, 20,
		this->tabs->getWindow()->getWindow(), (HMENU)ID_PRESETGENLISTHEADER, NULL, NULL);

	int listX = tabBoxCoords.left;
	int listY = tabBoxCoords.top + 20;
	int listHeight = tabHeight - 50;

	this->listBox = CreateWindowW(WC_LISTBOXW, NULL, WS_CHILD | LBS_NOTIFY,
		listX, listY, listWidth, listHeight, this->tabs->getWindow()->getWindow(),
		(HMENU)ID_PRESETGENLIST, musicGeneratorApp.getInstance(), NULL);

	for (auto it : Type::list) {
		std::vector<wchar_t> * buf = new std::vector<wchar_t>(it.begin(), it.end());
		buf->push_back(0);
		SendMessageW(this->listBox, LB_ADDSTRING, 0, (LPARAM)buf->data());
	}

	this->tabs->getWindow()->registerEventHandler(EventHandler::CreateCommandHandler(
		ID_PRESETGENLIST,
		LBN_SELCHANGE,
		std::bind(&PresetGeneratorTab::typeSelected, this, std::placeholders::_1)
	));

	int buttonContainerTop = tabBoxCoords.bottom - 120;
	int buttonContainerLeft = (int)(listWidth + ((tabWidth - listWidth) - 200) * 0.5);
	int buttonContainerWidth = 200;
	int buttonContainerHeight = 50;

	this->generateButton = CreateWindowW(WC_BUTTON, L"Generate", WS_CHILD,
		buttonContainerLeft, buttonContainerTop, buttonContainerWidth, buttonContainerHeight,
		this->tabs->getWindow()->getWindow(), (HMENU)ID_PRESETGENERATORSGENBUTTON, NULL, 0);

	this->tabs->getWindow()->registerEventHandler(EventHandler::CreateButtonClickedHandler(
		ID_PRESETGENERATORSGENBUTTON,
		std::bind(&PresetGeneratorTab::generateClick, this, std::placeholders::_1)
	));

	this->tabs->getWindow()->registerEventHandler(EventHandler::CreateCustomHandler(
		WM_PRESETGENTASKDONE,
		std::bind(&PresetGeneratorTab::generateDone, this, std::placeholders::_1)
	));

	this->generatorOptions->init();
}

void PresetGeneratorTab::typeSelected(Event * ev) {
	int item = ListBox_GetCurSel(this->listBox);
	this->generatorOptions->switchToType(item);
}

void PresetGeneratorTab::generateClick(Event * ev) {
	int item = ListBox_GetCurSel(this->listBox);
	if (item != LB_ERR) {
		if (this->canStartProcess) {
			if (this->generatorOptions->checkReadyState()) {
				this->canStartProcess = false;
				this->generateStart();
				this->runTask = new PresetGeneratorTask(this->tabs->getWindow());
				this->runTask->setOptionValues(this->generatorOptions->getOptionValues());
				this->runTaskThread = new std::thread(
					std::bind(&PresetGeneratorTask::run, this->runTask, std::placeholders::_1),
					item
				);
			}
		}
	}
	else {
		MessageBox(this->tabs->getWindow()->getWindow(), L"No Generator Selection", NULL, MB_APPLMODAL);
	}
}


void PresetGeneratorTab::generateDone(Event * ev) {
	this->runTaskThread->join();
	delete this->runTaskThread;
	this->canStartProcess = true;
	MessageBox(this->tabs->getWindow()->getWindow(), L"Generate Done", L"Generate Status", MB_APPLMODAL);
	Button_Enable(this->generateButton, true);
	ListBox_Enable(this->listBox, true);
	Button_SetText(this->generateButton, L"Generate");
}

void PresetGeneratorTab::generateStart() {
	ListBox_Enable(this->listBox, false);
	Button_Enable(this->generateButton, false);
	Button_SetText(this->generateButton, L"Generating...");
}

void PresetGeneratorTab::show() {
	ShowWindow(this->listBoxHeader, SW_SHOW);
	ShowWindow(this->listBox, SW_SHOW);
	ShowWindow(this->generateButton, SW_SHOW);
	this->generatorOptions->show();
}

void PresetGeneratorTab::hide() {
	ShowWindow(this->listBoxHeader, SW_HIDE);
	ShowWindow(this->listBox, SW_HIDE);
	ShowWindow(this->generateButton, SW_HIDE);
	this->generatorOptions->hide();
}

void PresetGeneratorTab::resize() {
	RECT tabBoxCoords;

	GetClientRect(this->tabs->getTabs(), &tabBoxCoords);
	TabCtrl_AdjustRect(this->tabs->getTabs(), false, &tabBoxCoords);

	int tabWidth = (tabBoxCoords.right - tabBoxCoords.left);
	int tabHeight = (tabBoxCoords.bottom - tabBoxCoords.top);

	int listHeaderX = tabBoxCoords.left;
	int listHeaderY = tabBoxCoords.top;

	int listWidth = (int)(tabWidth * 0.25);

	SetWindowPos(this->listBoxHeader, NULL, listHeaderX, listHeaderY, listWidth, 20, NULL);

	int listX = tabBoxCoords.left;
	int listY = tabBoxCoords.top + 20;
	int listHeight = tabHeight - 100;

	SetWindowPos(this->listBox, NULL, listX, listY, listWidth, listHeight, NULL);

	int buttonContainerWidth = 200;
	int buttonContainerHeight = 50;
	int buttonContainerTop = tabBoxCoords.bottom - 120;
	int buttonContainerLeft = (int)(listWidth + ((tabWidth - listWidth) - 200) * 0.5);

	SetWindowPos(this->generateButton, NULL, buttonContainerLeft, buttonContainerTop, buttonContainerWidth, buttonContainerHeight, NULL);

	this->generatorOptions->resize();
}

std::wstring PresetGeneratorTab::getName() {
	return L"Generators";
}
