#include "stdafx.h"
#include "MBStringUtils.h"
#include <string>

const wchar_t * GetWC(const char * str) {
	 size_t size = std::strlen(str) + 1;
	 wchar_t * wc = new wchar_t[size];
	 std::mbstowcs(wc, str, size);
	 return wc;
}
