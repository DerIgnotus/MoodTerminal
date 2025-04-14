#include "AnimationManager.hpp"

AnimationManager::AnimationManager(sf::RenderWindow& window, TerminalState& terminalState) : m_window(window), m_terminalState(terminalState)
{
    m_font.loadFromFile("Assets/Fonts/consolas.ttf");
    if (!m_font.loadFromFile("Assets/Fonts/consolas.ttf")) {
        std::cerr << "Failed to load font\n";
    }

	m_animationText.setFont(m_font);

    m_splashArt = {
        "===============================",
        "       MOOD TERMINAL 1.0",
        "===============================",
        "",
		"",
        "",
        "Initializing..."
    };
}

void AnimationManager::StartBootUpAnimation()
{
	m_terminalState = TerminalState::ANIMATION;

	m_activeAnimation = "startup";
}

void AnimationManager::StartClearScreenAnimation()
{
    m_terminalState = TerminalState::ANIMATION;

	m_activeAnimation = "clear";

    m_clearFrame = 0;
    m_clearMask = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));
}

void AnimationManager::StartAsciiWaveAnimation()
{
	m_terminalState = TerminalState::ANIMATION;
	m_activeAnimation = "ascii_wave";
}

void AnimationManager::Update()
{
	m_window.clear(sf::Color(10, 10, 10)); 

	if (m_activeAnimation == "startup") {
		UpdateBootUpAnimation();
	}
	else if (m_activeAnimation == "clear") {
		UpdateClearScreenAnimation();
    } 
    else if (m_activeAnimation == "ascii_wave") {
		float time = m_asciiWaveClock.getElapsedTime().asSeconds();
		DrawAsciiWave(time);
    }

    m_window.display();
}

void AnimationManager::UpdateBootUpAnimation()
{
    int y = 100;
    for (const auto& line : m_splashArt) {
        m_animationText.setString(line);
        m_animationText.setPosition(m_window.getSize().x / 2 - 275, y);
        m_window.draw(m_animationText);
        y += 25;
    }

    m_animationProgress += m_animationClock.restart().asSeconds() * m_bootSpeed;

    // Draw progress bar
    int totalBars = 30;
    int filledBars = static_cast<int>((m_animationProgress / 100.0f) * totalBars);
    std::string bar = "[" + std::string(filledBars, '#') + std::string(totalBars - filledBars, '-') + "]";

    std::string progressLine = bar + " " + std::to_string((int)m_animationProgress) + "%";
    m_animationText.setString(progressLine);
    m_animationText.setPosition(m_window.getSize().x / 2 - 275, y + 10);
    m_window.draw(m_animationText);

    if (m_animationProgress >= 100.0f) {
		m_activeAnimation = "";

		m_terminalState = TerminalState::TERMINAL;

        m_animationClock.restart();
        m_animationProgress = 0.0f;

        StartClearScreenAnimation();
    }
}

void AnimationManager::UpdateClearScreenAnimation()
{
    for (int y = 0; y < rows; ++y) {
        for (int x = 0; x < cols; ++x) {
            // Only draw if it's time for this cell
            if (x + y <= m_clearFrame) {
                m_clearMask[y][x] = true;

                sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
                cell.setPosition(x * cellSize, y * cellSize);
                cell.setFillColor(sf::Color::White);
                m_window.draw(cell);
            }
        }
    }

    m_clearFrame += 2;

    // Done when last diagonal finishes
    if (m_clearFrame > (cols + rows)) {
		m_activeAnimation = "";
		m_terminalState = TerminalState::TERMINAL;

        m_clearMask.clear();
    }
}

void AnimationManager::DrawAsciiWave(float time) {
    sf::Text ch;
    ch.setFont(m_font);
    ch.setCharacterSize(18);
    ch.setFillColor(sf::Color::White);

    float spacingX = 10.f; // Smaller spacing
    float spacingY = 8.f; // Keep some vertical distance
    int cols = m_window.getSize().x / spacingX;
    int rows = m_window.getSize().y / spacingY;

    for (int x = 0; x < cols; ++x) {
        float wave = std::sin(time * 4 / 1.2 + x * 0.1f);
        int y = int((wave + 1.0f) * 0.5f * (rows - 1));
        ch.setString("~");
        ch.setPosition(x * spacingX, y * spacingY);
        m_window.draw(ch);
    }
}



