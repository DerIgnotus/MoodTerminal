#include "Fireworks.hpp"

Fireworks::Fireworks(sf::RenderWindow& window) : m_window(window)
{
	m_lastSpawnTime_1 = 0.f;
	m_lastSpawnTime_2 = 0.f;
	m_lastSpawnTime_3 = 0.f;

	m_spawnNewFireworks_1 = rand() % 5 + 1;
	m_spawnNewFireworks_2 = rand() % 5 + 1; // Random number between 1 and 5
	m_spawnNewFireworks_3 = rand() % 5 + 1; 
}

void Fireworks::Update(sf::Color color)
{
    m_color = color;

	if (m_lastSpawnTime_1 >= m_spawnNewFireworks_1) {
		SpawnParticlesGoingUp(m_particlesGoingUp.size());
		m_lastSpawnTime_1 = 0.f;
        m_spawnNewFireworks_1 = rand() % 5 + 1;
	}
	if (m_lastSpawnTime_2 >= m_spawnNewFireworks_2) {
		SpawnParticlesGoingUp(m_particlesGoingUp.size());
		m_lastSpawnTime_2 = 0.f;
		m_spawnNewFireworks_2 = rand() % 5 + 1;
	}
    if (m_lastSpawnTime_3 >= m_spawnNewFireworks_3) {
        SpawnParticlesGoingUp(m_particlesGoingUp.size());
        m_lastSpawnTime_3 = 0.f;
        m_spawnNewFireworks_3 = rand() % 5 + 1;
    }


    for (auto it = m_particlesGoingUp.begin(); it != m_particlesGoingUp.end(); ) {
        auto& particle = *it;

        sf::Vector2f lastKnownPos;
        if (!particle.empty()) {
            lastKnownPos = particle[0].GetPosition();
        }

        for (auto& p : particle) {
            p.Update(0.1f);
            p.Draw(m_window);
        }

        particle.erase(
            std::remove_if(particle.begin(), particle.end(), [](const Particle& p) { return p.IsDead(); }),
            particle.end()
        );

        if (particle.empty()) {
            SpawnParticleExplosion(lastKnownPos);

            it = m_particlesGoingUp.erase(it);
        }
        else {
            ++it;
        }
    }


    for (auto& particle : m_particlesExplosion) {
        particle.Update(0.1f);
        particle.Draw(m_window);
    }

    // Erase dead explosion particles AFTER updating/drawing
    m_particlesExplosion.erase(
        std::remove_if(m_particlesExplosion.begin(), m_particlesExplosion.end(),
            [](const Particle& p) { return p.IsDead(); }),
        m_particlesExplosion.end()
    );

	m_lastSpawnTime_1 += 0.08f;
	m_lastSpawnTime_2 += 0.08f;
	m_lastSpawnTime_3 += 0.08f;
}

void Fireworks::SpawnParticles()
{
	
}

void Fireworks::SpawnParticlesGoingUp(int vec)  
{  
	m_particlesGoingUp.push_back(std::vector<Particle>()); // Create a new vector for the particles going up

	int numParticles = rand() % 16 + 10; // Random number of particles between 10 and 25 
	float posX = static_cast<float>(rand() % m_window.getSize().x); // Random X position within the window width
	float posY = static_cast<float>(m_window.getSize().y); // Start from the bottom of the window
	float lifeTime = static_cast<float>(rand() % 4 + 3); // Random lifetime between 3 and 6 seconds
	sf::Vector2f velocity = sf::Vector2f(0.f, static_cast<float>(-(rand() % 50 + 50))); // Upward velocity

	for (int i = 0; i < numParticles; ++i) {  
	sf::Vector2f pos = sf::Vector2f(posX, posY + i * 7);

		sf::CircleShape shape(5.f);  
		shape.setFillColor(m_color);

		m_particlesGoingUp[vec].emplace_back(pos, shape, m_color, lifeTime, velocity);
	}  
}

void Fireworks::SpawnParticleExplosion(sf::Vector2f position)  
{  
    int numParticles = rand() % 41 + 40; // Random number of particles between 40 and 80  
    float lifeTime = static_cast<float>(rand() % 3 + 3); // Random lifetime between 3 and 5 seconds  

    for (int i = 0; i < numParticles; ++i) {  
        float angle = static_cast<float>(rand() % 360); // Random angle in degrees  
        float speed = static_cast<float>(rand() % 100 + 50); // Random speed between 50 and 150  
        float speedDivide = static_cast<float>(rand() % 16 + 20) / 10.f; // Random speed divide between 2.0 and 3.5

        // Convert angle to radians and calculate velocity  
        float radian = angle * (3.14159f / 180.f);  
        sf::Vector2f velocity = sf::Vector2f(std::cos(radian) * speed / speedDivide, std::sin(radian) * speed / speedDivide);  

        sf::CircleShape shape(3.f); // Smaller particle size for explosion  
        shape.setFillColor(m_color); // Explosion particles are yellow  

        m_particlesExplosion.emplace_back(position, shape, m_color, lifeTime, velocity);
    }  
}
