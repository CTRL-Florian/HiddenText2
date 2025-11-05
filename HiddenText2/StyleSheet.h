#pragma once

#include <map>
#include <vector>
#include <iostream>

class StyleSheet
{
public:
	std::vector<bool> getLetter(char l);

protected:
	std::map<char, std::vector<bool>> mLetterMap;

private:
	virtual std::map<char, std::vector<bool>> initializeLetters() = 0;
};

class Standard : public StyleSheet
{
public:
	Standard();

private:
	std::map<char, std::vector<bool>> initializeLetters() override;
};