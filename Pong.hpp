#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Pong
{
public:
	Pong();
	void Update();

	int GetScore1() const { return m_score1; }
	int GetScore2() const { return m_score2; }

	sf::Text& GetScoreText1() { return m_scoreText1; }
	sf::Text& GetScoreText2() { return m_scoreText2; }

	void MovePaddle1(int dy) { m_paddle1.move(0, dy * m_paddleSpeed); }
	void MovePaddle2(int dy) { m_paddle2.move(0, dy * m_paddleSpeed); }

	sf::RectangleShape& GetPaddle1() { return m_paddle1; }
	sf::RectangleShape& GetPaddle2() { return m_paddle2; }

	int GetPaddleSpeed() const { return m_paddleSpeed; }

	sf::CircleShape& GetBall() { return m_ball; }

private:
	sf::Font m_font;

	sf::RectangleShape m_paddle1;
	sf::RectangleShape m_paddle2;
	
	sf::CircleShape m_ball;
	sf::Vector2f m_ballVelocity;

	sf::Text m_scoreText1;
	sf::Text m_scoreText2;

	int m_paddleSpeed = 5;
	float m_ballSpeed = 3;

	int m_score1 = 0;
	int m_score2 = 0;
};

