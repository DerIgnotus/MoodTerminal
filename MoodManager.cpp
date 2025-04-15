#include "MoodManager.hpp"

MoodManager::MoodManager()
{
	m_currentMood = NONE;

	m_mood = MoodToString(m_currentMood);

	std::cout << "Current mood: " << m_mood << std::endl;
}

void MoodManager::Update()
{
	if (m_currentMood == CRAZY)
	{
		float time = m_clock.getElapsedTime().asSeconds();

		// Smooth color waves for text
		int rText = static_cast<int>(std::sin(time * 2.0f) * 127 + 128);
		int gText = static_cast<int>(std::sin(time * 3.0f + 2.0f) * 127 + 128);
		int bText = static_cast<int>(std::sin(time * 1.5f + 4.0f) * 127 + 128);

		// Inverted or offset colors for background to contrast
		int rBg = 255 - rText;
		int gBg = 255 - gText;
		int bBg = 255 - bText;

		m_currentColorText = sf::Color(rText, gText, bText);
		m_currentColorBackground = sf::Color(rBg, gBg, bBg);
	}
}

bool MoodManager::SetMood(std::string& mood)
{
	std::cout << "Setting mood to: " << mood << std::endl;
	bool couldChange = StringToMood(mood);

	if (!couldChange)
	{
		std::cout << "Mood not found" << std::endl;
		return false;
	}

	m_mood = MoodToString(m_currentMood);

	return true;
}

std::vector<std::string> MoodManager::GetAvailableMoods()
{
	return { "Happy", "Sad", "Angry", "Excited", "Crazy", "None" };
}

bool MoodManager::StringToMood(std::string mood)
{
	transform(mood.begin(), mood.end(), mood.begin(), ::tolower);

	if (mood == "happy")
	{
		m_currentMood = HAPPY;
		return true;
	}
	else if (mood == "sad")
	{
		m_currentMood = SAD;
		return true;
	}
	else if (mood == "angry")
	{
		m_currentMood = ANGRY;
		return true;
	}
	else if (mood == "excited")
	{
		m_currentMood = EXCITED;
		return true;
	}
	else if (mood == "crazy")
	{
		m_currentMood = CRAZY;
		return true;
	}
	else if (mood == "none")
	{
		m_currentMood = NONE;
		return true;
	}
	else
	{
		std::cout << "Mood not found" << std::endl;
		return false;
	}
}

std::string MoodManager::MoodToString(MoodType mood)
{
	switch (mood)
	{
	case HAPPY:
		m_currentColorText = m_happyColorText;
		m_currentColorBackground = m_happyColorBackground;

		return "Happy";
	case SAD:
		m_currentColorText = m_sadColorText;
		m_currentColorBackground = m_sadColorBackground;

		return "Sad";
	case ANGRY:
		m_currentColorText = m_angryColorText;
		m_currentColorBackground = m_angryColorBackground;

		return "Angry";
	case EXCITED:
		m_currentColorText = m_excitedColorText;
		m_currentColorBackground = m_excitedColorBackground;

		return "Excited";
	case CRAZY:
		
		return "Crazy";
	case NONE:
		m_currentColorText = m_noneColorText;
		m_currentColorBackground = m_noneColorBackground;

		return "None";
	default:
		return "None";
	}
}
