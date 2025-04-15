#include "Pong.hpp"

Pong::Pong()
{
	m_font.loadFromFile("Assets/Fonts/consolas.ttf");
	if (!m_font.loadFromFile("Assets/Fonts/consolas.ttf")) {
		std::cerr << "Failed to load font\n";
	}

	m_paddle1.setSize(sf::Vector2f(10, 100));
	m_paddle1.setPosition(50, 250);

	m_paddle2.setSize(sf::Vector2f(10, 100));
	m_paddle2.setPosition(1140, 250);

	m_ball.setRadius(10);
	m_ball.setPosition(600, 300);
	m_ballVelocity = sf::Vector2f(-5.0f, -5.0f);

	m_scoreText1.setPosition(300, 50);
	m_scoreText2.setPosition(900, 50);

	m_scoreText1.setFont(m_font);
	m_scoreText2.setFont(m_font);

	m_scoreText1.setCharacterSize(40);
	m_scoreText2.setCharacterSize(40);

	m_scoreText1.setString(std::to_string(m_score1));
	m_scoreText2.setString(std::to_string(m_score2));
}

void Pong::Update()
{
    m_ball.move(m_ballVelocity * (static_cast<float>(m_ballSpeed) / 2.5f));
	
	if (m_ball.getPosition().x < 0)
	{
		m_score2++;
		m_ball.setPosition(600, 300);
		m_ballVelocity.x = -m_ballVelocity.x;

		m_scoreText2.setString(std::to_string(m_score2));

		m_ballSpeed = 3;
	}	

	if (m_ball.getPosition().x > 1200)
	{
		m_score1++;
		m_ball.setPosition(600, 300);
		m_ballVelocity.x = -m_ballVelocity.x;

		m_scoreText1.setString(std::to_string(m_score1));

		m_ballSpeed = 3;
	}

	if (m_ball.getPosition().y < 0 || m_ball.getPosition().y > 600 - 20)
	{
		m_ballVelocity.y = -m_ballVelocity.y;

		m_ballSpeed += 0.045f;
	}

	if (m_ball.getGlobalBounds().intersects(m_paddle1.getGlobalBounds()))
	{
		m_ballVelocity.x = -m_ballVelocity.x;
		m_ballSpeed += 0.045f;
	}
	if (m_ball.getGlobalBounds().intersects(m_paddle2.getGlobalBounds()))
	{
		m_ballVelocity.x = -m_ballVelocity.x;
		m_ballSpeed += 0.045f;
	}
}
