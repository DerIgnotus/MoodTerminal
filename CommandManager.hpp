#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <algorithm>
#include <ctime>
#include <chrono>
#include <random>

#include "History.hpp"
#include "MoodManager.hpp"
#include "AnimationManager.hpp"
#include "AudioManager.hpp"
#include "TerminalState.hpp"

class CommandManager
{
public:
	CommandManager(History& historyManager, MoodManager& moodManager, AnimationManager& animationManager, AudioManager& audioManager, TerminalState& terminalState);
	void ExecuteCommand(const std::string& command);
	void Update();

private:
	std::vector<std::string> m_commands;
	std::vector<std::string> m_commandDescriptions;

	float m_randomMoodChangeTime;
	bool m_virusActivated = false;

	std::random_device rd;
	std::mt19937 gen;

	History& m_historyManager;
	MoodManager& m_moodManager;
	AnimationManager& m_animationManager;
	AudioManager& m_audioManager;

	TerminalState& m_terminalState;

	std::vector<std::string> SplitInput(const std::string& input);

	void Help(std::vector<std::string>& args);
	void Clear(std::vector<std::string>& args);
	void Exit(std::vector<std::string>& args);
	void Mood(std::vector<std::string>& args);
	void MoodVirus(std::vector<std::string>& args);
	void MoodList(std::vector<std::string>& args);
	void Print(std::vector<std::string>& args);
	void Time(std::vector<std::string>& args);
	void Pong(std::vector<std::string>& args);
	void AsciiWave(std::vector<std::string>& args);
	void Fireworks(std::vector<std::string>& args);

	void Error(const std::string& message);
};

