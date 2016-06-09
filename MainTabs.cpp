#include "stdafx.h"

#include <vector>

#include "MusicGeneratorApp.h"
#include "MainWindow.h"
#include "MainTabs.h"
#include "PresetGeneratorTab.h"
#include "LogTab.h"
#include "EventHandler.h"
#include "Event.h"

MainTabs::MainTabs(MainWindow * mainWindow) {
	this->mainWindow = mainWindow;
	this->tabs = new std::map<int, Tab *>();
}

void MainTabs::init() {
	RECT size;
	GetWindowRect(this->mainWindow->getWindow(), &size);
	this->hTab = CreateWindowW(WC_TABCONTROLW, NULL, WS_CHILD | WS_VISIBLE,
		0, 0, size.right - size.left, size.bottom - size.top, this->mainWindow->getWindow(),
		(HMENU)ID_TABCTRLMENU, this->mainWindow->getApp()->getInstance(), NULL);

	Tab * presetGeneratorTab = new PresetGeneratorTab(this);
	presetGeneratorTab->addTab();
	this->tabs->insert_or_assign(presetGeneratorTab->getNumber(), presetGeneratorTab);
	currSelection = presetGeneratorTab;
	currSelection->show();

	
	Tab * logTab = new LogTab(this);
	logTab->addTab();
	this->tabs->insert_or_assign(logTab->getNumber(), logTab);

	this->getWindow()->registerEventHandler(EventHandler::CreateNotifyHandler(
		TCN_SELCHANGE,
		this->hTab,
		std::bind(&MainTabs::switchTab, this, std::placeholders::_1)
	));

	this->getWindow()->registerEventHandler(EventHandler::CreateSizeHandler(
		std::bind(&MainTabs::resize, this, std::placeholders::_1)
	));
}

void MainTabs::switchTab(Event * ev) {
	int currentSelection = TabCtrl_GetCurSel(this->hTab);
	this->currSelection->hide();
	Tab * selection = this->tabs->at(currentSelection);
	selection->resize();
	selection->show();
	this->currSelection = selection;
}

void MainTabs::resize(Event * ev) {
	RECT size;
	GetWindowRect(this->mainWindow->getWindow(), &size);
	SetWindowPos(this->hTab, NULL, 0, 0, size.right - size.left, size.bottom - size.top, NULL);
	this->currSelection->resize();
}

HWND MainTabs::getTabs() {
	return this->hTab;
}

MainWindow * MainTabs::getWindow() {
	return this->mainWindow;
}

Tab::Tab(MainTabs * mainTabs) {
	this->tabs = mainTabs;
}

void Tab::addTab() {
	TCITEMW tie;
	tie.mask = TCIF_TEXT;

	std::wstring name = this->getName();
	std::vector<wchar_t> * buf = new std::vector<wchar_t>(name.begin(), name.end());
	buf->push_back(0);
	tie.pszText = buf->data();

	int count = TabCtrl_GetItemCount(this->tabs->getTabs());
	this->number = TabCtrl_InsertItem(this->tabs->getTabs(), count, (LPTCITEM)&tie);

	this->init();
}

int Tab::getNumber() {
	return this->number;
}

MainTabs * Tab::getTabs() {
	return this->tabs;
}
