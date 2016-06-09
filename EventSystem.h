#pragma once

#include "stdafx.h"
#include "EventHandler.h"
#include <map>
#include <vector>

class MainWindow;

class EventSystem {
protected:
	MainWindow * mainWindow;
	std::map<std::wstring, std::vector<EventHandler *> *> * eventMap;

public:
	EventSystem(MainWindow *);

	bool handle(UINT, WPARAM, LPARAM);
	void registerHandler(EventHandler *);
};
