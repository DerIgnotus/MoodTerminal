#include "AudioManager.hpp"


AudioManager::AudioManager()
{
	if (!m_typingBuffer.loadFromFile("Assets/Sounds/Keyboard-Click.wav")) {
		std::cerr << "Error loading beep sound!" << std::endl;
	}
	m_typingSound.setVolume(10 / 1.5f);
	if (!m_errorBuffer.loadFromFile("Assets/Sounds/Error-Beep.wav")) {
		std::cerr << "Error loading error sound!" << std::endl;
	}
	m_errorSound.setVolume(13 / 1.5f);
	if (!m_enterBuffer.loadFromFile("Assets/Sounds/Press Enter.wav")) {
		std::cerr << "Error loading enter sound!" << std::endl;
	}
	m_enterSound.setVolume(18 / 1.5f);
	if (!m_startupBuffer.loadFromFile("Assets/Sounds/Startup-Sound.wav")) {
		std::cerr << "Error loading startup sound!" << std::endl;
	}
	m_startupSound.setVolume(30 / 1.5f);
	if (!m_backgroundBuffer.loadFromFile("Assets/Sounds/Background Noise.wav")) {
		std::cerr << "Error loading background sound!" << std::endl;
	}
	m_backgroundSound.setVolume(30 / 1.5f);
}

void AudioManager::PlaySound(const std::string& sound)
{
	if (sound == "typing") {
		m_typingSound.setBuffer(m_typingBuffer);
		m_typingSound.play();
	}
	else if (sound == "error") {
		m_errorSound.setBuffer(m_errorBuffer);
		m_errorSound.play();
	}
	else if (sound == "enter") {
		m_enterSound.setBuffer(m_enterBuffer);
		m_enterSound.play();
	}
	else if (sound == "startup") {
		m_startupSound.setBuffer(m_startupBuffer);
		m_startupSound.play();
	}
	else if (sound == "background") {
		m_backgroundSound.setBuffer(m_backgroundBuffer);
		m_backgroundSound.setLoop(true);
		m_backgroundSound.play();
	}
	else {
		std::cerr << "Unknown sound: " << sound << std::endl;
	}
}
