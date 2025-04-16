#pragma once

#include <SFML/Graphics.hpp>

class Particle
{
public:
	Particle(sf::Vector2f position, sf::CircleShape shape, sf::Color color, float lifeTime, sf::Vector2f velocity);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	bool IsDead() const { return m_isDead;  }
	float GetLifeTime() const { return m_lifeTime; }
	sf::Vector2f GetPosition() const { return m_position; }

private:
	sf::Vector2f m_position;
	sf::CircleShape m_shape;
	sf::Color m_color;
	float m_lifeTime;
	sf::Vector2f m_velocity;
	bool m_isDead;
};

