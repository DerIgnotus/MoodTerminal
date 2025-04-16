#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

#include "Particle.hpp"

class Fireworks
{
public:
    Fireworks(sf::RenderWindow& window);
	void Update(sf::Color color);

private:
	sf::RenderWindow& m_window;

	std::vector<Particle> m_particlesExplosion;
	std::vector<std::vector<Particle>> m_particlesGoingUp;

	sf::Color m_color;

	float m_spawnNewFireworks_1;
	float m_lastSpawnTime_1;
	float m_spawnNewFireworks_2;
	float m_lastSpawnTime_2;
	float m_spawnNewFireworks_3;
	float m_lastSpawnTime_3;

	void SpawnParticles();
	void SpawnParticlesGoingUp(int vec);
	void SpawnParticleExplosion(sf::Vector2f position);
};

