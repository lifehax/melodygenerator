#pragma once

#include "MIDITrack.h"
#include "vector"
#include "map"
#include "string"

class SongGenerator;
class TrackOptionItem;


class Type {
private:
	int number;
	std::wstring name;
	std::map<std::string, std::string> * optionValues;
public:
	Type(int, std::wstring);
	int getTickResolution();
	void setOptionValues(std::map<std::string, std::string> *);
	std::string getOptionValue(std::string);
	virtual int getBpm() = 0;
	virtual int getMicroSecondsPerNote() = 0;
	virtual int64_t getSongLength() = 0;
	virtual SongGenerator * getGenerator(MIDITrack * target) = 0;
	std::wstring getName();

	virtual std::map<std::string, std::pair<std::string, std::map<std::string, std::string>>> * getOptions();

	static const std::vector<std::wstring> list;
	static std::map<std::wstring, Type *(*)(int, std::wstring)> classMap;
	static Type * CreateFromName(std::wstring name);
	static Type * Create(int);
};

template<typename T> Type * createTypeFactory(int number, std::wstring name) {
	return (Type *)new T(number, name);
}
