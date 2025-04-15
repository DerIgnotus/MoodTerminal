#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

#include "History.hpp"
#include "MoodManager.hpp"
#include "Pong.hpp"


class TerminalRenderer
{
public:
	TerminalRenderer(sf::RenderWindow& window, History& historyManager, MoodManager& moodManager, Pong& pongGame);

	void Draw(const std::vector<std::string>& history, const std::string& input, int cursorPos);
	void ResetCursorBlinkTime() { m_currentCursorBlinkTime = m_cursorBlinkTime; }
	void Update();
	void DrawPongGame();

private:
	const int m_topDistance = 8; 
	const std::string m_prompt = "MoodTerminal>";
	const float m_cursorBlinkTime = 0.5f;

	MoodManager& m_moodManager;
	Pong& m_pongGame;

	float m_currentCursorBlinkTime = 0.5f;
	int m_scrollOffset = 0;

	sf::RenderWindow& m_window;
	sf::Font m_font;
	
	sf::Text m_terminalText;
	sf::Text m_historyText;
	sf::Text m_cursorText;
	sf::Text m_inputText;

	History& m_historyManager;
	
	void TextInit();
	int DrawHistory(const std::vector<std::string>& history, int& currentTextPos);
	int GetCursorPosition(int& cursorPos);
	void SetOffset();
};

