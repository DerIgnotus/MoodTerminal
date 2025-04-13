#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "TerminalRenderer.hpp"
#include "CommandManager.hpp"
#include "InputHandler.hpp"
#include "History.hpp"
#include "MoodManager.hpp"
#include "AnimationManager.hpp"
#include "AudioManager.hpp"

class Terminal
{
public:
	Terminal();
	void Run();

private:
	sf::RenderWindow m_window;	

	std::unique_ptr<AudioManager> m_audioManager;
	std::unique_ptr<AnimationManager> m_animationManager;
	std::unique_ptr<History> m_historyManager;
	std::unique_ptr<TerminalRenderer> m_terminalRenderer;
	std::unique_ptr<CommandManager> m_commandManager;
	std::unique_ptr<InputHandler> m_inputHandler;
	std::unique_ptr<MoodManager> m_moodManager;
};

