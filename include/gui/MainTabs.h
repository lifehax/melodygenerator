#pragma once
#include "stdafx.h"

#include <map>
#include <string>

class MainWindow;
class Tab;
class Event;

class MainTabs {
protected:
	MainWindow * mainWindow;
	HWND hTab;
	std::map<int, Tab *> * tabs;
	Tab * currSelection;
public:
	MainTabs(MainWindow *);
	void init();
	HWND getTabs();
	MainWindow * getWindow();
	void switchTab(Event *);
	void resize(Event *);
};

class Tab {
protected:
	MainTabs * tabs;
	int number;
public:
	Tab(MainTabs *);
	void addTab();
	virtual void init() = 0;
	virtual std::wstring getName() = 0;
	virtual void show() = 0;
	virtual void hide() = 0;
	virtual void resize() = 0;
	int getNumber();
	MainTabs * getTabs();
};
