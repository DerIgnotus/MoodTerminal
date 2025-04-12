#include "History.hpp"

History::History()
{

}

void History::AddToHistory(const std::string& command)
{
	//m_history.push_back(m_prompt + command);
	m_history.push_back(command);
}

void History::ClearHistory()
{
	m_history.clear();

	AddToHistory("Welcome to the Mood Terminal!");
}

