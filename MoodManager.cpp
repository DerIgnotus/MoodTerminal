#include "MoodManager.hpp"

MoodManager::MoodManager()
{
	m_currentMood = NONE;

	m_mood = MoodToString(m_currentMood);

	std::cout << "Current mood: " << m_mood << std::endl;
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
	return { "Happy", "Sad", "Angry", "Excited", "None" };
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
		return "Happy";
	case SAD:
		return "Sad";
	case ANGRY:
		return "Angry";
	case EXCITED:
		return "Excited";
	case NONE:
		return "None";
	default:
		return "None";
	}

}
