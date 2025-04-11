#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Terminal
{
public:
	Terminal();
	~Terminal();
	void Run();

private:
	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_historyText;
	sf::Text m_typeText;
	sf::Text m_inputText;
	std::string m_input;
	std::vector<std::string> m_history;
	std::string m_prompt = "MoodTerminal>";
	int m_historyIndex;
	int m_historySize = 1;
	int m_topDistance = 10;
	int m_typeAt = 0;

	void ProcessInput();
	void Draw();
	void Update();
	void PolleEvents();
	void ExecuteCommand(const std::string& command);
	void AddToHistory(const std::string& command);
	void AddCharacter(char character, int index);
};

