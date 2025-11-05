#include "StyleSheet.h"

std::vector<bool> StyleSheet::getLetter(char l)
{
	if (mLetterMap.find(l) == mLetterMap.end()) {
		std::cout << "Character " << l << " not in stylesheet." << std::endl;
		return std::vector<bool>(15, false);
	} 

	return mLetterMap[l];
}

Standard::Standard()
{
	mLetterMap = initializeLetters();
}

std::map<char, std::vector<bool>> Standard::initializeLetters()
{
	std::map<char, std::vector<bool>> map;

	std::vector<bool> letter;

	// a
	letter = { false, true, false,
				true, true, true,
				true, false, true,
				true, true, true,
				true, false, true };

	map['a'] = letter;

	// b
	letter = 
}