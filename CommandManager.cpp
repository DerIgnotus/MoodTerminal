#include "CommandManager.hpp"

CommandManager::CommandManager(History& historyManager, MoodManager& moodManager, AnimationManager& animationManager, AudioManager& audioManager, TerminalState& terminalState)
	: m_historyManager(historyManager), m_moodManager(moodManager), m_animationManager(animationManager), m_audioManager(audioManager), m_terminalState(terminalState),
	m_randomMoodChangeTime(static_cast<float>(rand() % 21 + 10)) // Random time between 10 and 30
{
	gen = std::mt19937(rd()); // Initialize the random number generator

	m_commands.push_back("help");
	m_commandDescriptions.push_back("Displays the list of available commands.");

	m_commands.push_back("clear");
	m_commandDescriptions.push_back("Clears the terminal screen.");

	m_commands.push_back("exit");
	m_commandDescriptions.push_back("Exits the terminal.");

	m_commands.push_back("mood");
	m_commandDescriptions.push_back("Gets the mood for the terminal.");

	m_commands.push_back("moodvirus");
	m_commandDescriptions.push_back("Randomly changes the mood of the terminal.");

	m_commands.push_back("moodlist");
	m_commandDescriptions.push_back("Displays the list of available moods.");
	
	m_commands.push_back("print");
	m_commandDescriptions.push_back("Prints the provided text to the terminal.");

	m_commands.push_back("time");
	m_commandDescriptions.push_back("Displays the current time.");

	m_commands.push_back("pong");
	m_commandDescriptions.push_back("Starts the pong game.");

	m_commands.push_back("asciiwave");
	m_commandDescriptions.push_back("Starts the ASCII wave animation.");

	m_commands.push_back("fireworks");
	m_commandDescriptions.push_back("Starts the fireworks animation.");
}

void CommandManager::ExecuteCommand(const std::string& command)
{
	m_historyManager.AddToHistory("MoodTerminal>" + command);
	
	std::vector<std::string> commandParts = SplitInput(command);
	std::string mainCommand = commandParts[0];
	std::vector<std::string> arguments(commandParts.begin() + 1, commandParts.end());

	transform(mainCommand.begin(), mainCommand.end(), mainCommand.begin(), ::tolower);

	std::cout << "Command: " << mainCommand << std::endl;

	if (mainCommand == "help") {
		Help(arguments);
	}
	else if (mainCommand == "clear") {
		Clear(arguments);
	}
	else if (mainCommand == "exit") {
		Exit(arguments);
	}
	else if (mainCommand == "mood") {
		Mood(arguments);
	}
	else if (mainCommand == "moodvirus") {
		MoodVirus(arguments);
	}
	else if (mainCommand == "moodlist") {
		MoodList(arguments);
	}
	else if (mainCommand == "print") {
		Print(arguments);
	}
	else if (mainCommand == "time") {
		Time(arguments);
	} 
	else if (mainCommand == "pong") {
		Pong(arguments);
	}
	else if (mainCommand == "asciiwave") {
		AsciiWave(arguments);
	}
	else if (mainCommand == "fireworks") {
		Fireworks(arguments);
	}
	else {
		Error("Unknown command: " + mainCommand);
	}

	m_historyManager.AddToHistory("\n");
}

void CommandManager::Update()
{
	if (m_virusActivated) {
		m_randomMoodChangeTime -= 0.04f; // Decrease the time until the next mood change
		if (m_randomMoodChangeTime <= 0) {
			std::string mood = m_moodManager.GetMood();

			while (mood == m_moodManager.GetMood()) {
				std::uniform_int_distribution<> distrib(0, m_moodManager.GetAvailableMoods().size() - 1);
				int randomMoodIndex = distrib(gen);

				m_moodManager.SetMood(m_moodManager.GetAvailableMoods()[randomMoodIndex]);
			}

			m_historyManager.AddToHistory("Mood Virus changed the mood from '" + mood + "' to '" + m_moodManager.GetMood() + "'");

			m_randomMoodChangeTime = static_cast<float>(rand() % 21 + 10); // Reset to a new random time between 10 and 30
		}
	}
}

std::vector<std::string> CommandManager::SplitInput(const std::string& input) {
	std::stringstream ss(input);
	std::string word;
	std::vector<std::string> result;

	while (ss >> word)
		result.push_back(word);

	return result;
}

void CommandManager::Help(std::vector<std::string>& args)
{
	if (args.size() > 1) {
		std::cout << "Help command accepts only one argument." << std::endl;
		Error("Help command accepts only one argument.");
		return;
	}
	if (args.size() == 1) {

		return;
	}

	std::cout << "Available commands:" << std::endl;
	for (int i = 0; i < m_commands.size(); i++) {
		std::string text = m_commands[i] + " - " + m_commandDescriptions[i];

		std::cout << text << std::endl;
		m_historyManager.AddToHistory(text);
	}

	m_historyManager.AddToHistory("\n");
	m_historyManager.AddToHistory("For more information about each command, type HELP + command.");
}

void CommandManager::Clear(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "Clear command does not accept any arguments." << std::endl;
		Error("Clear command does not accept any arguments.");
		return;
	}

	m_historyManager.ClearHistory();
	m_animationManager.StartClearScreenAnimation();
}

void CommandManager::Exit(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "Exit command does not accept any arguments." << std::endl;
		Error("Exit command does not accept any arguments.");
		return;
	}

	std::cout << "Exiting the terminal..." << std::endl;
	m_historyManager.AddToHistory("Exiting the terminal...");

	exit(0);
}

void CommandManager::Mood(std::vector<std::string>& args)
{
	if (args.size() > 1) {
		std::cout << "Mood command accepts only one argument." << std::endl;
		Error("Mood command accepts only one argument.");
		return;
	}

	if (args.empty()) {
		std::cout << "Current mood: " << m_moodManager.GetMood() << std::endl;
		m_historyManager.AddToHistory("Current mood: " + m_moodManager.GetMood());
		return;
	}
	
	std::string moodBeforeChange = m_moodManager.GetMood();
	
	bool moodExists = m_moodManager.SetMood(args[0]);

	if (moodBeforeChange != m_moodManager.GetMood()) {
		std::cout << "Mood changed from " << moodBeforeChange << " to " << m_moodManager.GetMood() << std::endl;
		m_historyManager.AddToHistory("Mood changed from " + moodBeforeChange + " to " + m_moodManager.GetMood());
	}
	else if (moodBeforeChange == m_moodManager.GetMood() && moodExists) {
		std::cout << "Mood is already set to '" << args[0] << "'" << std::endl;
		m_historyManager.AddToHistory("Mood is already set to '" + args[0] + "'");
	}
	else 
	{
		std::cout << "Mood '" << args[0] <<  "' doesn't exist!" << std::endl;
		m_historyManager.AddToHistory("Mood '" + args[0] + "' doesn't exist!");
	}
}

void CommandManager::MoodVirus(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "MoodVirus command does not accept any arguments." << std::endl;
		Error("MoodVirus command does not accept any arguments.");
		return;
	}

	m_virusActivated = !m_virusActivated;
}

void CommandManager::MoodList(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "MoodList command does not accept any arguments." << std::endl;
		Error("MoodList command does not accept any arguments.");
		return;
	}
	std::cout << "Available moods:" << std::endl;
	m_historyManager.AddToHistory("Available moods:");

	for (const auto& mood : m_moodManager.GetAvailableMoods()) {
		std::cout << mood << std::endl;
		m_historyManager.AddToHistory(mood);
	}
}

void CommandManager::Print(std::vector<std::string>& args)
{
	std::string text = "";

	if (args.empty()) {
		std::cout << "No arguments provided for print command." << std::endl;
		Error("No arguments provided for print command.");
		return;
	}

	for (const auto& arg : args) {
		text += arg + " ";
	}

	m_historyManager.AddToHistory(text);
}

void CommandManager::Time(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "Time command does not accept any arguments." << std::endl;
		Error("Time command does not accept any arguments.");
		return;
	}

	std::time_t t = std::time(0);  
	std::tm* now = std::localtime(&t);

	std::ostringstream timeString;
	timeString
		<< (now->tm_mday) << '-'                // Day of the month
		<< (now->tm_mon + 1) << '-'             // Month (tm_mon is 0-11, so add 1)
		<< (now->tm_year + 1900) << " "         // Year (tm_year is years since 1900)
		<< (now->tm_hour) << ':'                // Hour
		<< (now->tm_min) << ':'                 // Minute
		<< (now->tm_sec);                       // Second

	timeString.str();
	std::string time = timeString.str();
	
	std::cout << "Current time: " << time << std::endl;
	m_historyManager.AddToHistory("Current time: " + time);
}

void CommandManager::Pong(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "Pong command does not accept any arguments." << std::endl;
		Error("Pong command does not accept any arguments.");
		return;
	}

	m_terminalState = TerminalState::PONG;
}

void CommandManager::AsciiWave(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "AsciiWave command does not accept any arguments." << std::endl;
		Error("AsciiWave command does not accept any arguments.");
		return;
	}

	m_animationManager.StartAsciiWaveAnimation();
}

void CommandManager::Fireworks(std::vector<std::string>& args)
{
	if (!args.empty()) {
		std::cout << "Fireworks command does not accept any arguments." << std::endl;
		Error("Fireworks command does not accept any arguments.");
		return;
	}

	m_animationManager.StartFireworksAnimation();
}

void CommandManager::Error(const std::string& message)
{
	std::cerr << "Error: " << message << std::endl;
	m_historyManager.AddToHistory("Error: " + message);

	m_audioManager.PlaySound("error");
}

