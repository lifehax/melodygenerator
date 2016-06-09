#pragma once

#include <map>
#include <vector>

class TrackOptionItem;
class MainWindow;
class PresetGeneratorTab;

class PresetGeneratorOptions {
protected:
	bool noOptions = false;
	int currSelection = -1;

	PresetGeneratorTab * tab;
	MainWindow * mainWindow;

	HWND optionArea;
	HWND optionDefaultText;
	HWND noOptionsText;


	std::map<int, std::map<std::string, TrackOptionItem *> *> * controls;
public:
	PresetGeneratorOptions(PresetGeneratorTab *, MainWindow *);

	void init();
	void switchToType(int item);
	void showHideOptions();
	void show();
	void hide();
	void resize();
	MainWindow * getWindow();
	HWND getOptionArea();
	bool checkReadyState();
	std::map<std::string, std::string> * getOptionValues();
};
