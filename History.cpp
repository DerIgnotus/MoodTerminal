#include "History.hpp"

History::History()
{

}

void History::AddToHistory(const std::string& command)
{
	//m_history.push_back(m_prompt + command);
	m_history.push_back(command);
}

void History::AddToHistoryCommands(const std::string& command)  
{  
   if (m_historyCommands.empty() || m_historyCommands[0] != "")  
   {  
       m_historyCommands.insert(m_historyCommands.begin(), "");  
   }  
   m_historyCommands.insert(m_historyCommands.begin() + 1, command);  
   //m_historyCommands.push_back(command);  
}

void History::ClearHistory()
{
	m_history.clear();

	AddToHistory("Welcome to the Mood Terminal!");
}

