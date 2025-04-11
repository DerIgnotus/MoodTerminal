#pragma once

#include "History.hpp"
#include "CommandManager.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

class InputHandler
{
public:
	InputHandler(sf::RenderWindow& window, History& historyManager, CommandManager& commandManager);
	void PolleEvents();
	std::string GetInput() const { return m_input; }
	int GetCursorPos() const { return m_cursorPos; }
private:
	sf::RenderWindow& m_window;
	std::string m_input;
	int m_cursorPos = 0;

	History& m_historyManager;
	CommandManager& m_commandManager;
	void AddCharacter(char character, int index);
};

