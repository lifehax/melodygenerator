#include "stdafx.h"
#include "PresetGeneratorTask.h"
#include "Generator.h"
#include "MainWindow.h"

PresetGeneratorTask::PresetGeneratorTask(MainWindow * mainWindow) {
	this->mainWindow = mainWindow;
	this->optionValues = new std::map<std::string, std::string>();
}

void PresetGeneratorTask::run(int typeNum) {
	Generator generator;
	generator.setOptionValues(this->optionValues);
	generator.generate(typeNum);
	PostMessage(this->mainWindow->getWindow(), WM_PRESETGENTASKDONE, NULL, NULL);
}

void PresetGeneratorTask::setOptionValues(std::map<std::string, std::string> * optionValues) {
	this->optionValues = optionValues;
}