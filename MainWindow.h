#pragma once

#include "resource.h"
#include "stdafx.h"
#include <map>
#include <vector>


class MusicGeneratorApp;
class AboutBox;
class MainTabs;
class EventSystem;
class EventHandler;

class MainWindow {
private:
	HWND hWnd;
	MusicGeneratorApp * app;
	AboutBox * aboutBox;
	MainTabs * mainTabs;
	EventSystem * eventSystem;
public:
	MainWindow(MusicGeneratorApp * app);
	HWND getWindow();
	MusicGeneratorApp * getApp();

	void registerEventHandler(EventHandler *);

	void initTabs(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
	LRESULT CALLBACK proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};
