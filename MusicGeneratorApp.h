#pragma once

#include "resource.h"
#include "MainWindow.h"

class MusicGeneratorApp {
protected:
	// Global Variables:
	HINSTANCE hInst;                                // current instance
	WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
	WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

	HWND mainWindowHandle;
	MainWindow * mainWindow;

public:
	MusicGeneratorApp();
	int APIENTRY winMain(_In_ HINSTANCE hInstance,
		_In_opt_ HINSTANCE hPrevInstance,
		_In_ LPWSTR    lpCmdLine,
		_In_ int       nCmdShow);
	ATOM registerClass(HINSTANCE hInstance);
	BOOL initInstance(HINSTANCE hInstance, int nCmdShow);
	HINSTANCE getInstance();
	MainWindow * getWindow(HWND);
};

extern MusicGeneratorApp musicGeneratorApp;
