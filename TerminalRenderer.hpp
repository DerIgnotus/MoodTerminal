#pragma once
#include <SFML/Graphics.hpp>
#include "History.hpp"
#include <iostream>

class TerminalRenderer
{
public:
	TerminalRenderer(sf::RenderWindow& window, History& historyManager);

	void Draw(const std::vector<std::string>& history, const std::string& input, int cursorPos);
private:
	const int m_topDistance = 10;
	const std::string m_prompt = "MoodTerminal>";

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
};

