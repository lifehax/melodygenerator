#pragma once

#include "MainTabs.h"
#include <thread>

class Event;
class PresetGeneratorTask;
class PresetGeneratorOptions;

class PresetGeneratorTab : public Tab {
protected:
	HWND listBox;
	HWND listBoxHeader;
	HWND generateButton;

	std::thread * runTaskThread;
	PresetGeneratorTask * runTask;
	PresetGeneratorOptions * generatorOptions;

	int currListBoxSelection;
	bool canStartProcess;
public:
	PresetGeneratorTab(MainTabs *);
	virtual void init();
	virtual std::wstring getName();

	void typeSelected(Event *);
	void generateClick(Event *);

	virtual void generateDone(Event * ev);
	virtual void generateStart();
	virtual void show();
	virtual void hide();
	virtual void resize();
};
