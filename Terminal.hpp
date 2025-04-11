#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "TerminalRenderer.hpp"
#include "CommandManager.hpp"
#include "InputHandler.hpp"
#include "History.hpp"

class Terminal
{
public:
	Terminal();
	void Run();

private:
	sf::RenderWindow m_window;	

	void WindowInit();
	sf::Font FontInit();

	std::shared_ptr<History> m_historyManager;
	std::shared_ptr<TerminalRenderer> m_terminalRenderer;
	std::shared_ptr<CommandManager> m_commandManager;
	std::shared_ptr<InputHandler> m_inputHandler;
};

