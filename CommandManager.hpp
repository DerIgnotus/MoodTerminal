#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>

#include "History.hpp"
#include "MoodManager.hpp"
#include "AnimationManager.hpp"


class CommandManager
{
public:
	CommandManager(History& historyManager, MoodManager& moodManager, AnimationManager& animationManager);
	void ExecuteCommand(const std::string& command);

private:
	std::vector<std::string> m_commands;
	std::vector<std::string> m_commandDescriptions;

	History& m_historyManager;
	MoodManager& m_moodManager;
	AnimationManager& m_animationManager;

	std::vector<std::string> SplitInput(const std::string& input);

	void Help(std::vector<std::string>& args);
	void Clear(std::vector<std::string>& args);
	void Exit(std::vector<std::string>& args);
	void Mood(std::vector<std::string>& args);
	void MoodList(std::vector<std::string>& args);
	void Print(std::vector<std::string>& args);

	void Error(const std::string& message);
};

