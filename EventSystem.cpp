#include "stdafx.h"
#include "EventSystem.h"
#include "Event.h"
#include "EventHandler.h"

EventSystem::EventSystem(MainWindow * mainWindow) {
	this->mainWindow = mainWindow;
	this->eventMap = new std::map<std::wstring, std::vector<EventHandler *> *>();
}

bool EventSystem::handle(UINT msg, WPARAM wparam, LPARAM lparam) {
	bool hasHandledEvent = false;
	std::wstring key = EventHandler::GetHandlerKey(msg, wparam, lparam);
	auto handlers = this->eventMap->find(key);
	if (handlers != this->eventMap->end()) {
		Event * ev = new Event(msg, wparam, lparam);
		for (auto handler : *handlers->second) {
			handler->invoke(ev);
			hasHandledEvent = true;
		}
	}
	return hasHandledEvent;
}

void EventSystem::registerHandler(EventHandler * handler) {
	std::wstring key = handler->getHandlerKey();
	auto handlers = this->eventMap->find(key);
	if (handlers == this->eventMap->end()) {
		this->eventMap->insert_or_assign(
			key,
			new std::vector<EventHandler *>()
		);
	}
	(*(this->eventMap))[key]->push_back(handler);
}
