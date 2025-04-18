#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>

#include "TerminalState.hpp"
#include "MoodManager.hpp"
#include "Fireworks.hpp"

class AnimationManager
{
public:
	AnimationManager(sf::RenderWindow& window, TerminalState& terminalState, MoodManager& moodManager, Fireworks& fireworks);
	void StartBootUpAnimation();
	void StartClearScreenAnimation();
	void StartAsciiWaveAnimation();
	void StartFireworksAnimation();
	void Update();

private:
	sf::RenderWindow& m_window;
	TerminalState& m_terminalState;

	MoodManager& m_moodManager;
	Fireworks& m_fireworks;

	std::string m_activeAnimation;

	std::vector<std::string> m_splashArt;
	sf::Clock m_animationClock;
	float m_animationProgress = 0.0f;
	float m_bootSpeed = 28.0f;
	

	const int cellSize = 25;
	int cols = m_window.getSize().x / cellSize;
	int rows = m_window.getSize().y / cellSize;

	std::vector<std::vector<bool>> m_clearMask;
	int m_clearFrame = 0;
	
	
	sf::Clock m_asciiWaveClock;


	sf::Text m_animationText;
	sf::Font m_font;

	
	void DrawAsciiWave(float time);
	void UpdateBootUpAnimation();
	void UpdateClearScreenAnimation();
	void UpdateFireworksAnimation();
};

