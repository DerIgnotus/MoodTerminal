#include "InputHandler.hpp"

InputHandler::InputHandler(sf::RenderWindow& window, History& historyManager, CommandManager& commandManager, TerminalRenderer& terminalRenderer, 
	AudioManager& audioManager, TerminalState& terminalState, Pong& pongGame)
	: m_window(window), m_historyManager(historyManager), m_commandManager(commandManager), m_terminalRenderer(terminalRenderer), 
	m_audioManager(audioManager), m_terminalState(terminalState), m_pongGame(pongGame)
{
}

void InputHandler::PolleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		else if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == 8) { // Backspace
				if (!m_input.empty()) {
					m_input.pop_back();
					m_cursorPos--;
				}
			}
			else if (event.text.unicode == 13) { // Enter
				if (!m_input.empty()) {
					m_commandManager.ExecuteCommand(m_input);
					m_historyManager.AddToHistoryCommands(m_input);
					m_input.clear();
					m_cursorPos = 0;

					m_historyManager.SetHistoryCommandsIndex(0);

					m_audioManager.PlaySound("enter");
				}
			}
			else if (event.text.unicode == 27) { // Escape
				if (m_terminalState == TerminalState::TERMINAL)
					m_window.close();
				else
					m_terminalState = TerminalState::TERMINAL;
			}
			else if (event.text.unicode < 128) {
				AddCharacter(static_cast<char>(event.text.unicode), m_cursorPos);
				m_cursorPos++;
			}

			m_audioManager.PlaySound("typing");
			m_terminalRenderer.ResetCursorBlinkTime();
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
				if (m_cursorPos > 0)
					m_cursorPos--;
			if (event.key.code == sf::Keyboard::Right)
				if (m_cursorPos < m_input.size())
					m_cursorPos++;
			if (event.key.code == sf::Keyboard::Up)
			{
				if (m_historyManager.GetHistoryCommandsIndex() < m_historyManager.GetHistoryCommandsSize() - 1) // Prevent out-of-bounds
				{
					m_historyManager.SetHistoryCommandsIndex(m_historyManager.GetHistoryCommandsIndex() + 1);
					m_input = m_historyManager.GetHistoryCommands()[m_historyManager.GetHistoryCommandsIndex()];

					m_cursorPos = m_input.size();
				}
			}
			if (event.key.code == sf::Keyboard::Down)
			{
				if (m_historyManager.GetHistoryCommandsIndex() > 0) // Prevent out-of-bounds
				{
					m_historyManager.SetHistoryCommandsIndex(m_historyManager.GetHistoryCommandsIndex() - 1); // Decrement first
					m_input = m_historyManager.GetHistoryCommands()[m_historyManager.GetHistoryCommandsIndex()];

					m_cursorPos = m_input.size();
				}
				else
				{
					m_input.clear(); // Clear input if at the bottom of the history

					m_cursorPos = m_input.size();
				}
			}

			m_audioManager.PlaySound("typing");
			m_terminalRenderer.ResetCursorBlinkTime();
		}
	}
}

void InputHandler::StandartPollEvents()
{
	sf::Event event;

	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				if (m_terminalState == TerminalState::TERMINAL)
					m_window.close();
				else
					m_terminalState = TerminalState::TERMINAL;
			}
		}
	}
}

void InputHandler::PongPollEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		else if (event.type == sf::Event::KeyPressed) {
			if (event.key.code == sf::Keyboard::Escape) {
				m_terminalState = TerminalState::TERMINAL;
			}
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_pongGame.MovePaddle1(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_pongGame.MovePaddle1(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
		m_pongGame.MovePaddle2(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		m_pongGame.MovePaddle2(1);
	}
}

void InputHandler::AddCharacter(char character, int index)
{
	if (index >= 0 && index <= m_input.size()) {
		m_input.insert(m_input.begin() + index, character);
	}
}
