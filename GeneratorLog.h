#pragma once

#include <string>
#include <vector>
#include <functional>

class GeneratorLog {
protected:
	int debugLogLevel;
	static GeneratorLog * instance;
	std::wstring logData;
	std::vector<std::function<void(std::wstring)>> * listeners;

	GeneratorLog();
public:
	void log(std::wstring);
	static GeneratorLog * I();
	static void Log(std::wstring);
	static void LogMsg(std::wstring);
	static void LogDebug(int, std::wstring);
	static void LogError(std::wstring);
	static void LogWarn(std::wstring);

	static void RegisterListener(std::function<void(std::wstring)>);
};