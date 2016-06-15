#pragma once

#include <map>

class MainWindow;

class PresetGeneratorTask {
protected:
	MainWindow * mainWindow;
	std::map<std::string, std::string> * optionValues;
public:
	PresetGeneratorTask(MainWindow *);
	void run(int typeNum);
	void setOptionValues(std::map<std::string, std::string> *);
};
