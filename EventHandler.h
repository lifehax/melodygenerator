#pragma once

#include <functional>

class Event;

class EventHandler {
protected:
	unsigned int eventMsg;
	unsigned int wParamLoWord;
	unsigned int wParamHighWord;
	unsigned int notifyMsgForCode;
	unsigned int notifyMsgForWindow;

	std::function<void(Event *)> callback;

	EventHandler(std::function<void(Event *)>);

	void setEventMsg(unsigned int);
	void setWParamLoWord(unsigned int);
	void setWParamHighWord(unsigned int);
	void setNotifyMsgForCode(unsigned int);
	void setNotifyMsgForWindow(unsigned int);
public:

	void invoke(Event *);

	std::wstring getHandlerKey();
	static std::wstring GetHandlerKey(UINT message, WPARAM wParam, LPARAM lParam);

	static EventHandler * CreateNotifyHandler(unsigned int handleCode, HWND targetWindow, std::function<void(Event *)> callback);
	static EventHandler * CreateButtonClickedHandler(unsigned int buttonID, std::function<void(Event *)> callback);
	static EventHandler * CreateCommandHandler(unsigned int id, unsigned int code, std::function<void(Event *)> callback);
	static EventHandler * CreateSizeHandler(std::function<void(Event *)>);
	static EventHandler * CreateCustomHandler(unsigned int msg, std::function<void(Event *)>);
};
