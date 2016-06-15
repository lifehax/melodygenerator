#include "stdafx.h"

#include <string>
#include "Event.h"
#include "EventHandler.h"

EventHandler::EventHandler(std::function<void(Event *)> callback) {
	this->callback = callback;
	this->eventMsg = 0;
	this->wParamLoWord = 0;
	this->wParamHighWord = 0;
	this->notifyMsgForCode = 0;
	this->notifyMsgForWindow = 0;
}

void EventHandler::invoke(Event * ev) {
	this->callback(ev);
}

void EventHandler::setEventMsg(unsigned int eventMsg) {
	this->eventMsg = eventMsg;
}

void EventHandler::setWParamLoWord(unsigned int wParamLoWord) {
	this->wParamLoWord = wParamLoWord;
}

void EventHandler::setWParamHighWord(unsigned int wParamHighWord) {
	this->wParamHighWord = wParamHighWord;
}

void EventHandler::setNotifyMsgForCode(unsigned int notifyMsgForCode) {
	this->notifyMsgForCode = notifyMsgForCode;
}

void EventHandler::setNotifyMsgForWindow(unsigned int notifyMsgForWindow) {
	this->notifyMsgForWindow = notifyMsgForWindow;
}


std::wstring EventHandler::getHandlerKey() {
	return std::to_wstring(this->eventMsg) + std::to_wstring(this->wParamLoWord) + std::to_wstring(this->wParamHighWord)
			+ std::to_wstring(this->notifyMsgForCode) + std::to_wstring(this->notifyMsgForWindow);
}

std::wstring EventHandler::GetHandlerKey(UINT message, WPARAM wParam, LPARAM lParam) {
	if (message == WM_NOTIFY) {
		LPNMHDR handle = (LPNMHDR)lParam;
		return std::to_wstring(message) + std::to_wstring(0) + std::to_wstring(0)
			+ std::to_wstring(handle->code) + std::to_wstring(handle->idFrom);
	} else if(message == WM_COMMAND) {
		return std::to_wstring(message) + std::to_wstring(LOWORD(wParam)) + std::to_wstring(HIWORD(wParam))
			+ std::to_wstring(0) + std::to_wstring(0);
	} else {
		return std::to_wstring(message) + std::to_wstring(0) + std::to_wstring(0)
			+ std::to_wstring(0) + std::to_wstring(0);
	}
}

EventHandler * EventHandler::CreateNotifyHandler(unsigned int handleCode, HWND targetWindow, std::function<void(Event *)> callback) {
	EventHandler * eventHandler = new EventHandler(callback);
	eventHandler->setEventMsg(WM_NOTIFY);
	eventHandler->setNotifyMsgForCode(handleCode);
	eventHandler->setNotifyMsgForWindow(GetDlgCtrlID(targetWindow));
	return eventHandler;
}

EventHandler * EventHandler::CreateButtonClickedHandler(unsigned int buttonID, std::function<void(Event *)> callback) {
	EventHandler * eventHandler = new EventHandler(callback);
	eventHandler->setEventMsg(WM_COMMAND);
	eventHandler->setWParamLoWord(buttonID);
	eventHandler->setWParamHighWord(BN_CLICKED);
	return eventHandler;
}

EventHandler * EventHandler::CreateSizeHandler(std::function<void(Event *)> callback) {
	EventHandler * eventHandler = new EventHandler(callback);
	eventHandler->setEventMsg(WM_SIZE);
	return eventHandler;
}

EventHandler * EventHandler::CreateCustomHandler(unsigned int msg, std::function<void(Event *)> callback) {
	EventHandler * eventHandler = new EventHandler(callback);
	eventHandler->setEventMsg(msg);
	return eventHandler;
}

EventHandler * EventHandler::CreateCommandHandler(unsigned int id, unsigned int code, std::function<void(Event *)> callback) {
	EventHandler * eventHandler = new EventHandler(callback);
	eventHandler->setEventMsg(WM_COMMAND);
	eventHandler->setWParamLoWord(id);
	eventHandler->setWParamHighWord(code);
	return eventHandler;
}
