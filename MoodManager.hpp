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

	sf::Color GetTextColor() { return m_currentColorText; };
	sf::Color GetBackgroundColor() { return m_currentColorBackground; };

private:
	enum MoodType
	{
		HAPPY,
		SAD,
		ANGRY,
		EXCITED,
		NONE,
	};


	// NONE (already provided)
	const sf::Color m_noneColorText = sf::Color(255, 255, 255);
	const sf::Color m_noneColorBackground = sf::Color(10, 10, 10);

	// HAPPY
	const sf::Color m_happyColorText = sf::Color(255, 223, 88);       // Warm golden yellow
	const sf::Color m_happyColorBackground = sf::Color(30, 30, 15);   // Soft, sunlit brownish

	// SAD
	const sf::Color m_sadColorText = sf::Color(135, 206, 250);        // Light sky blue
	const sf::Color m_sadColorBackground = sf::Color(15, 20, 35);     // Deep navy blue

	// ANGRY
	const sf::Color m_angryColorText = sf::Color(255, 90, 90);        // Reddish pink
	const sf::Color m_angryColorBackground = sf::Color(40, 10, 10);   // Dark crimson-like tone

	// EXCITED
	const sf::Color m_excitedColorText = sf::Color(255, 105, 180);    // Vibrant pink
	const sf::Color m_excitedColorBackground = sf::Color(30, 0, 40);  // Deep purple/black mix


	std::string m_mood;
	MoodType m_currentMood;

	sf::Color m_currentColorText = sf::Color(255, 255, 255);
	sf::Color m_currentColorBackground = sf::Color(10, 10, 10);

	

	bool StringToMood(std::string mood);
	std::string MoodToString(MoodType mood);
};

