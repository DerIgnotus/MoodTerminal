#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "History.hpp"



class CommandManager
{
public:
	CommandManager(History& historyManager);
	void ExecuteCommand(const std::string& command);

private:
	std::vector<std::string> m_commands;

	History& m_historyManager;

	std::vector<std::string> SplitInput(const std::string& input);

	void Help(std::vector<std::string>& args);
	void Clear(std::vector<std::string>& args);
	void Exit(std::vector<std::string>& args);
	void Mood(std::vector<std::string>& args);
	void MoodList(std::vector<std::string>& args);
	void SetMood(std::vector<std::string>& args);
	void Print(std::vector<std::string>& args);

	void Error(const std::string& message);
};

