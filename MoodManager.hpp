#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>

class MoodManager
{
public: 
	MoodManager();
	bool SetMood(std::string& mood);
	std::string GetMood() { return m_mood; }
	std::vector<std::string> GetAvailableMoods();

private:
	enum MoodType
	{
		HAPPY,
		SAD,
		ANGRY,
		EXCITED,
		NONE,
	};

	std::string m_mood;
	MoodType m_currentMood;

	bool StringToMood(std::string mood);
	std::string MoodToString(MoodType mood);
};

