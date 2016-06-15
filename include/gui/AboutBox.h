#pragma once
#include "stdafx.h"

class MainWindow;

class AboutBox {
protected:
	MainWindow * mainWindow;
public:
	AboutBox(MainWindow *);
	INT_PTR CALLBACK proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static INT_PTR CALLBACK Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};
