#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

#include "History.hpp"
#include "CommandManager.hpp"
#include "TerminalRenderer.hpp"
#include "AudioManager.hpp"
#include "TerminalState.hpp"

class InputHandler
{
public:
	InputHandler(sf::RenderWindow& window, History& historyManager, CommandManager& commandManager, TerminalRenderer& terminalRenderer, AudioManager& audioManager, TerminalState& terminalState);
	void PolleEvents();
	void StandartPollEvents();
	std::string GetInput() const { return m_input; }
	int GetCursorPos() const { return m_cursorPos; }

private:
	

	sf::RenderWindow& m_window;
	std::string m_input;
	int m_cursorPos = 0;

	History& m_historyManager;
	CommandManager& m_commandManager;
	TerminalRenderer& m_terminalRenderer;
	AudioManager& m_audioManager;
	TerminalState& m_terminalState;



	void AddCharacter(char character, int index);
};

