#pragma once

#include <vector>
#include <string>
#include <map>

#define NoteDef std::pair<std::string, double>

class Note {
private:
public:
	static const std::vector<std::string> wholeNotes;
	static const std::vector<std::string> halfNotes;
	static const std::vector<std::string> allNotes;
	static const std::map<std::string, int> idxMap;
	static const std::map<std::string, std::vector<int>> typeNums;
	static const std::vector<std::string> leadToFollowNotes;
	static const std::vector<NoteDef> notes;


	static bool Note::isAugmentedFifth(std::string note1, std::string note2);
	static bool Note::isPerfectFifth(std::string note1, std::string note2);
	static bool Note::isDiminishedFifth(std::string note1, std::string note2);
	static bool Note::isPerfectFourth(std::string note1, std::string note2);
	static bool Note::isMajorThird(std::string note1, std::string note2);
	static bool Note::isMinorThird(std::string note1, std::string note2);
	static bool Note::isOctave(std::string note1, std::string note2);
	static std::pair<int, int> * Note::pitchRatio(std::string note1, std::string note2);
};
