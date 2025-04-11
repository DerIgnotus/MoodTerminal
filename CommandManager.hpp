#pragma once

#include <SFML/Graphics.hpp>
#include "History.hpp"

class CommandManager
{
public:
	CommandManager(History& historyManager);
	void ExecuteCommand(const std::string& command);

private:
	History& m_historyManager;
};

