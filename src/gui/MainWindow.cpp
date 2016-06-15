#include "stdafx.h"

#include <string>

#include "MainWindow.h"
#include "MusicGeneratorApp.h"
#include "AboutBox.h"
#include "MainTabs.h"
#include "EventSystem.h"

MainWindow::MainWindow(MusicGeneratorApp * app) {
	this->app = app;
	this->aboutBox = new AboutBox(this);
	this->mainTabs = new MainTabs(this);
	this->eventSystem = new EventSystem(this);
	this->hWnd = NULL;
}

LRESULT CALLBACK MainWindow::proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	if (message >= WM_USER && message <= 0xBFFF) {
		if (!this->eventSystem->handle(message, wParam, lParam)) {
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	} else {
		switch (message) {
		case WM_CREATE:
		{
			if (this->hWnd == NULL) {
				this->hWnd = hWnd;
				this->mainTabs->init();
			}
			break;
		}
		case WM_COMMAND:
		{
			int wmId = LOWORD(wParam);
			switch (wmId) {
			case IDM_ABOUT:
				DialogBoxParam(this->app->getInstance(), MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, AboutBox::Proc, (LPARAM)this->aboutBox);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			default:
				if (!this->eventSystem->handle(message, wParam, lParam)) {
					return DefWindowProc(hWnd, message, wParam, lParam);
				}
			}
			break;
		}
		case WM_NOTIFY:
		{
			this->eventSystem->handle(message, wParam, lParam);
			break;
		}
		case WM_SIZE:
		{
			this->eventSystem->handle(message, wParam, lParam);
			break;
		}
		case WM_PAINT:
		{
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			break;
		}
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
	}
	return 0;
}

HWND MainWindow::getWindow() {
	return this->hWnd;
}

MusicGeneratorApp * MainWindow::getApp() {
	return this->app;
}

LRESULT CALLBACK MainWindow::Proc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
	MainWindow * window = musicGeneratorApp.getWindow(hWnd);
	return window ? window->proc(hWnd, message, wParam, lParam) : (INT_PTR)FALSE;
}

void MainWindow::registerEventHandler(EventHandler * handler) {
	this->eventSystem->registerHandler(handler);
}
