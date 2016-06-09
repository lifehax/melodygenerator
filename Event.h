#pragma once

#include "stdafx.h"

class Event {
protected:
	UINT msg;
	WPARAM wparam;
	LPARAM lparam;

public:
	Event(UINT msg, WPARAM wparam, LPARAM lparam);
	LPNMHDR getNotifyData();
};