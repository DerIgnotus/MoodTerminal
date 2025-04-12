#pragma once

#include <SFML/Audio.hpp>
#include <iostream>


class AudioManager
{
public:
	AudioManager();
	void PlaySound(const std::string& sound);

private:
	sf::SoundBuffer m_typingBuffer;
	sf::Sound m_typingSound;

	sf::SoundBuffer m_errorBuffer;
	sf::Sound m_errorSound;

	sf::SoundBuffer m_enterBuffer;
	sf::Sound m_enterSound;

	sf::SoundBuffer m_startupBuffer;
	sf::Sound m_startupSound;

	sf::SoundBuffer m_backgroundBuffer;
	sf::Sound m_backgroundSound;
};

