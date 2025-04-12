#include "AnimationManager.hpp"

AnimationManager::AnimationManager(sf::RenderWindow& window) : m_window(window)
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
	m_isAnimationActive = true;

	while (m_isAnimationActive)
	{
		UpdateBootUpAnimation();
	}

	m_animationClock.restart();
	m_animationProgress = 0.0f;
	StartClearScreenAnimation();
}

void AnimationManager::StartClearScreenAnimation()
{
	m_isAnimationActive = true;
    m_clearFrame = 0;
    m_clearMask = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

	while (m_isAnimationActive)
	{
		UpdateClearScreenAnimation();
	}
}

void AnimationManager::UpdateBootUpAnimation()
{
    m_window.clear(sf::Color(10, 10, 10));

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
        m_isAnimationActive = false;
    }

    m_window.display();
}

void AnimationManager::UpdateClearScreenAnimation()
{
    m_window.clear(sf::Color(10, 10, 10)); // Background color

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
        m_isAnimationActive = false;
        m_clearMask.clear();
    }

    m_window.display();
}

