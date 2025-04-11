#include "History.hpp"

History::History()
{

}

void History::AddToHistory(const std::string& command)
{
	//m_history.push_back(m_prompt + command);
	m_history.push_back(command);
}