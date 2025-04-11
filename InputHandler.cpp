#include "InputHandler.hpp"

InputHandler::InputHandler(sf::RenderWindow& window, History& historyManager, CommandManager& commandManager) : m_window(window), m_historyManager(historyManager), m_commandManager(commandManager)
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
					m_input.clear();
					m_cursorPos = 0;
				}
			}
			else if (event.text.unicode == 27) // Escape
				m_window.close();
			else if (event.text.unicode < 128) {
				AddCharacter(static_cast<char>(event.text.unicode), m_cursorPos);
				m_cursorPos++;
			}
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
				break;
			if (event.key.code == sf::Keyboard::Down)
				break;
		}
	}
}

void InputHandler::AddCharacter(char character, int index)
{
	if (index >= 0 && index <= m_input.size()) {
		m_input.insert(m_input.begin() + index, character);
	}
}
