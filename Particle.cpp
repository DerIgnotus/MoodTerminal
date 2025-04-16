#include "Particle.hpp"

Particle::Particle(sf::Vector2f position, sf::CircleShape shape, sf::Color color, float lifeTime, sf::Vector2f velocity)
	: m_position(position), m_shape(shape), m_color(color), m_lifeTime(lifeTime), m_velocity(velocity), m_isDead(false)
{
	m_shape.setPosition(m_position);
	m_shape.setFillColor(m_color);
}


void Particle::Update(float deltaTime)
{
	m_lifeTime -= deltaTime;
	if (m_lifeTime <= 0) {
		m_isDead = true;
	}
	else {
		m_position += m_velocity * deltaTime;
	}
}

void Particle::Draw(sf::RenderWindow& window)
{
	m_shape.setPosition(m_position);
	window.draw(m_shape);
}
