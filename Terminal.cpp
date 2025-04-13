#include "Terminal.hpp"

Terminal::Terminal()
	: m_window(sf::VideoMode(1200, 600), "Mood Terminal"),
	m_audioManager(std::make_unique<AudioManager>()),
	m_moodManager(std::make_unique<MoodManager>()),
	m_historyManager(std::make_unique<History>()),
	m_animationManager(std::make_unique<AnimationManager>(m_window)),
	m_commandManager(std::make_unique<CommandManager>(*m_historyManager, *m_moodManager, *m_animationManager, *m_audioManager)),
	m_terminalRenderer(std::make_unique<TerminalRenderer>(m_window, *m_historyManager)),
	m_inputHandler(std::make_unique<InputHandler>(m_window, *m_historyManager, *m_commandManager, *m_terminalRenderer, *m_audioManager))
{
	m_window.setFramerateLimit(60);
}

void Terminal::Run()
{
	m_audioManager->PlaySound("startup");
	m_animationManager->StartBootUpAnimation();
	m_audioManager->PlaySound("background");

	while (m_window.isOpen()) {

		if (m_animationManager->IsAnimationActive())
			return;
		
		m_inputHandler->PolleEvents();
		m_terminalRenderer->Draw(m_historyManager->GetHistory(), m_inputHandler->GetInput(), m_inputHandler->GetCursorPos());
	}
}


