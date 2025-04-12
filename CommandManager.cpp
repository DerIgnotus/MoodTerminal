#include "CommandManager.hpp"

CommandManager::CommandManager(History& historyManager) : m_historyManager(historyManager) 
{
	m_commands.push_back("help");
	m_commands.push_back("clear");
	m_commands.push_back("exit");
	m_commands.push_back("mood");
	m_commands.push_back("moodlist");
	m_commands.push_back("setmood");
	m_commands.push_back("print");
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

	}
	else if (mainCommand == "clear") {

	}
	else if (mainCommand == "exit") {

	}
	else if (mainCommand == "mood") {

	}
	else if (mainCommand == "moodlist") {

	}
	else if (mainCommand == "setmood") {

	}
	else if (mainCommand == "print") {
		Print(arguments);
	}
	else {
		std::cout << "Unknown command: " << mainCommand << std::endl;
		m_historyManager.AddToHistory("Unknown command: " + mainCommand);
	}

	m_historyManager.AddToHistory("\n");
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

void CommandManager::Error(const std::string& message)
{
	std::cerr << "Error: " << message << std::endl;
	m_historyManager.AddToHistory("Error: " + message);
}
