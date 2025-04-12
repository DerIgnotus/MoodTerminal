#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

class AnimationManager
{
public:
	AnimationManager(sf::RenderWindow& window);
	void StartBootUpAnimation();
	bool IsAnimationActive() const { return m_isAnimationActive; }
	void StartClearScreenAnimation();

private:
	sf::RenderWindow& m_window;

	std::vector<std::string> m_splashArt;

	bool m_isAnimationActive;
	sf::Clock m_animationClock;
	float m_animationProgress = 0.0f;
	float m_bootSpeed = 28.0f; 

	sf::Text m_animationText;
	sf::Font m_font;

	const int cellSize = 25; // Size of each cell (can be adjusted)
	int cols = m_window.getSize().x / cellSize;
	int rows = m_window.getSize().y / cellSize;

	std::vector<std::vector<bool>> m_clearMask; // True = already filled
	int m_clearFrame = 0;


	void UpdateBootUpAnimation();
	void UpdateClearScreenAnimation();
};

