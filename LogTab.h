#pragma once

#include "MainTabs.h"

class Event;

class LogTab : public Tab {
protected:
	HWND generateLog;
public:
	LogTab(MainTabs *);
	virtual void init();
	virtual std::wstring getName();

	void logListen(std::wstring);
	virtual void show();
	virtual void hide();
	virtual void resize();
};
