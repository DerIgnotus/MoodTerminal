#include "CommandManager.hpp"

CommandManager::CommandManager(History& historyManager) : m_historyManager(historyManager) 
{

}

void CommandManager::ExecuteCommand(const std::string& command)
{
	m_historyManager.AddToHistory("MoodTerminal>" + command);
}