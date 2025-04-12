#include "TerminalRenderer.hpp"

TerminalRenderer::TerminalRenderer(sf::RenderWindow& window, History& historyManager) : m_window(window), m_historyManager(historyManager)
{
	TextInit();
}


void TerminalRenderer::Draw(const std::vector<std::string>& history, const std::string& input, int cursorPos)
{
	int currentTextPos = 0;
	
	m_window.clear(sf::Color::Color(10, 10, 10));
	
	m_inputText.setString(input);
	m_terminalText.setString(m_prompt);

	SetOffset();

	currentTextPos = DrawHistory(history, currentTextPos);

	m_terminalText.setPosition(10, currentTextPos + m_topDistance - m_scrollOffset);
	m_inputText.setPosition(m_terminalText.getGlobalBounds().left + m_terminalText.getGlobalBounds().width + 1, currentTextPos + m_topDistance - m_scrollOffset);

	int cursorX = GetCursorPosition(cursorPos);

	// Set the position of the cursor
	m_cursorText.setPosition(cursorX, m_terminalText.getPosition().y);

	m_currentCursorBlinkTime -= 0.015f;

	if (m_currentCursorBlinkTime >= 0.0) {
		m_window.draw(m_cursorText);
	}
	else if (m_currentCursorBlinkTime <= -0.5f) {
		m_currentCursorBlinkTime = m_cursorBlinkTime;
	}

	m_window.draw(m_terminalText);
	m_window.draw(m_inputText);

	m_window.display();
}



int TerminalRenderer::DrawHistory(const std::vector<std::string>& history, int& currentTextPos)
{
	for (int i = 0; i < history.size(); i++) {
		m_historyText.setString(history[i]);
		m_historyText.setPosition(10, i * 20 + m_topDistance - m_scrollOffset);

		m_window.draw(m_historyText);

		currentTextPos += 20;
	}

	return currentTextPos;
}

int TerminalRenderer::GetCursorPosition(int& cursorPos)
{
	int cursorX = 5;

	for (int i = 0; i < m_terminalText.getString().getSize(); i++) {
		sf::Uint32 character = m_terminalText.getString()[i];
		const sf::Glyph& glyph = m_font.getGlyph(character, m_terminalText.getCharacterSize(), false);
		cursorX += glyph.advance;
	}

	for (int i = 0; i < m_inputText.getString().getSize(); i++) {
		if (i < cursorPos)
		{
			sf::Uint32 character = m_inputText.getString()[i];
			const sf::Glyph& glyph = m_font.getGlyph(character, m_inputText.getCharacterSize(), false);
			cursorX += glyph.advance;
		}
	}

	return cursorX;
}

void TerminalRenderer::SetOffset()
{
	int historySize = m_historyManager.GetHistorySize();

	if (historySize > 20) {
		m_scrollOffset = (historySize - 20) * 20 - 8;
	}
	else {
		m_scrollOffset = 0;
	}
}

void TerminalRenderer::TextInit()
{
	m_font.loadFromFile("Assets/Fonts/consolas.ttf");
	if (!m_font.loadFromFile("Assets/Fonts/consolas.ttf")) {
		std::cerr << "Failed to load font\n";
	}

	m_terminalText = sf::Text();
	m_terminalText.setFont(m_font);
	m_terminalText.setCharacterSize(20);
	m_terminalText.setFillColor(sf::Color::White);
	m_terminalText.setLetterSpacing(1);

	m_historyText = sf::Text();
	m_historyText.setFont(m_font);
	m_historyText.setCharacterSize(20);
	m_historyText.setFillColor(sf::Color::White);
	m_historyText.setLetterSpacing(1);

	m_cursorText = sf::Text();
	m_cursorText.setFont(m_font);
	m_cursorText.setCharacterSize(20);
	m_cursorText.setFillColor(sf::Color::White);
	m_cursorText.setLetterSpacing(1);
	m_cursorText.setString("|");

	m_inputText = sf::Text();
	m_inputText.setFont(m_font);
	m_inputText.setCharacterSize(20);
	m_inputText.setFillColor(sf::Color::White);
	m_inputText.setLetterSpacing(1);

	m_historyText.setString("Welcome to the Mood Terminal!");
	m_historyManager.AddToHistory(m_historyText.getString());

	m_historyManager.AddToHistory("\n");
}
