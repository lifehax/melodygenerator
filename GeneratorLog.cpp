#include "stdafx.h"
#include "GeneratorLog.h"

GeneratorLog * GeneratorLog::instance = NULL;

GeneratorLog::GeneratorLog() {
	this->logData = L"";
	this->listeners = new std::vector<std::function<void(std::wstring)>>();
	this->debugLogLevel = 4;
}

void GeneratorLog::log(std::wstring msg) {
	for (auto listener : *(this->listeners)) {
		listener(msg + L"\n");
	}
	this->logData += (msg + L"\n");
}

GeneratorLog * GeneratorLog::I() {
	if (GeneratorLog::instance == NULL) {
		GeneratorLog::instance = new GeneratorLog();
	}
	return GeneratorLog::instance;
}


void GeneratorLog::Log(std::wstring msg) {
	GeneratorLog::I()->log(msg);
}

void GeneratorLog::LogMsg(std::wstring msg) {
	GeneratorLog::I()->log(L"[MESSAGE]: " + msg);
}

void GeneratorLog::LogDebug(int level, std::wstring msg) {
	if (GeneratorLog::I()->debugLogLevel <= level) {
		GeneratorLog::I()->log(L"[DEBUG]: " + msg);
	}
}

void GeneratorLog::LogError(std::wstring msg) {
	GeneratorLog::I()->log(L"[ERROR]: " + msg);
}

void GeneratorLog::LogWarn(std::wstring msg) {
	GeneratorLog::I()->log(L"[WARN]: " + msg);
}

void GeneratorLog::RegisterListener(std::function<void(std::wstring)> listenerFunc) {
	GeneratorLog::I()->listeners->push_back(listenerFunc);
}
