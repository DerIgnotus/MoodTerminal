#include "Terminal.hpp"

Terminal::Terminal()
{
    m_window.create(sf::VideoMode(800, 450), "Mood Terminal");
    m_window.setFramerateLimit(60);

    m_font;
    if (!m_font.loadFromFile("Assets/Fonts/consolas.ttf")) {
        std::cerr << "Failed to load font\n";
    }

	m_text.setFont(m_font);
	m_text.setCharacterSize(16);
	m_text.setFillColor(sf::Color::White);
	m_text.setLetterSpacing(1);

	m_historyText.setFont(m_font);
	m_historyText.setCharacterSize(16);
	m_historyText.setFillColor(sf::Color::White);
	m_historyText.setLetterSpacing(1);

	m_typeText.setFont(m_font);
	m_typeText.setCharacterSize(16);
	m_typeText.setFillColor(sf::Color::White);
	m_typeText.setLetterSpacing(1);
	m_typeText.setString("|");

	m_inputText.setFont(m_font);
	m_inputText.setCharacterSize(16);
	m_inputText.setFillColor(sf::Color::White);
	m_inputText.setLetterSpacing(1);

	m_historyText.setString("Welcome to the Mood Terminal!");
	m_history.push_back(m_historyText.getString());
	m_historySize++;
}

Terminal::~Terminal()
{
}

void Terminal::Run()
{
	while (m_window.isOpen()) {
		PolleEvents();
		ProcessInput();
		Update();
		Draw();
	}
}

void Terminal::ProcessInput()
{
}

void Terminal::Draw()
{
	m_window.clear(sf::Color::Color(10, 10, 10));

	int currentTextPos = 0;

	// Draw history
	for (int i = 0; i < m_history.size(); i++) {
		m_historyText.setString(m_history[i]);
		m_historyText.setPosition(10, i * 20 + m_topDistance);
		m_window.draw(m_historyText);

		currentTextPos += 20; // Increment position for next line
	}

	// Draw the prompt and user input text
	m_text.setPosition(10, currentTextPos + 25);
	m_inputText.setPosition(m_text.getGlobalBounds().left + m_text.getGlobalBounds().width, currentTextPos + 25);

	float cursorX = 5;

	for (int i = 0; i < m_text.getString().getSize(); i++) {
		sf::Uint32 character = m_text.getString()[i];
		const sf::Glyph& glyph = m_font.getGlyph(character, m_text.getCharacterSize(), false);
		cursorX += glyph.advance; 
	}

	for (int i = 0; i < m_inputText.getString().getSize(); i++) {
		if (i < m_typeAt)
		{
			sf::Uint32 character = m_inputText.getString()[i];
			const sf::Glyph& glyph = m_font.getGlyph(character, m_inputText.getCharacterSize(), false);
			cursorX += glyph.advance;
		}
	}

	// Set the position of the cursor
	m_typeText.setPosition(cursorX, m_text.getPosition().y);

	// Draw the text and the cursor
	m_window.draw(m_text);
	m_window.draw(m_typeText);
	m_window.draw(m_inputText);

	m_window.display();
}


void Terminal::Update()
{
	m_inputText.setString(m_input);
	m_text.setString(m_prompt);
}

void Terminal::PolleEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			m_window.close();
		else if (event.type == sf::Event::TextEntered) {
			if (event.text.unicode == 8) { // Backspace
				if (!m_input.empty()) {
					m_input.pop_back();
					m_typeAt--;
				}
			}
			else if (event.text.unicode == 13) { // Enter
				if (!m_input.empty()) {
					AddToHistory(m_input);
					ExecuteCommand(m_input);
					m_input.clear();
					m_typeAt = 0;
				}
			}
			else if (event.text.unicode == 27) { // Escape
				m_window.close();
			}
			else if (event.text.unicode < 128) {
				//m_input += static_cast<char>(event.text.unicode);

				// WRONG, ALWAYS ADDS AT THE END

				AddCharacter(static_cast<char>(event.text.unicode), m_typeAt);


				m_typeAt++;
			}
		}
		else if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Left)
				if (m_typeAt > 0)
					m_typeAt--;
			if (event.key.code == sf::Keyboard::Right)
				if (m_typeAt < m_input.size())
					m_typeAt++;
			if (event.key.code == sf::Keyboard::Up)
				break;
			if (event.key.code == sf::Keyboard::Down)
				break;
		}
	}
}

void Terminal::ExecuteCommand(const std::string& command)
{

}

void Terminal::AddToHistory(const std::string& command)
{
	m_history.push_back(m_prompt + command);
	m_historySize++;
}

void Terminal::AddCharacter(char character, int index)
{
    if (index >= 0 && index <= m_input.size()) {
        m_input.insert(m_input.begin() + index, character);
    }
}

