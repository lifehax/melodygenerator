#include "stdafx.h"
#include "Event.h"

Event::Event(UINT msg, WPARAM wparam, LPARAM lparam) {
	this->msg = msg;
	this->wparam = wparam;
	this->lparam = lparam;
}

LPNMHDR Event::getNotifyData() {
	return (LPNMHDR)this->lparam;
}