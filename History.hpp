#pragma once

#include <SFML/Graphics.hpp>

class History
{
public:
	History();

	void AddToHistory(const std::string& command);
	void AddToHistoryCommands(const std::string& command);

	std::vector<std::string> GetHistory() const { return m_history; }
	std::vector<std::string> GetHistoryCommands() const { return m_historyCommands; }

	int GetHistorySize() { return m_history.size(); }
	int GetHistoryCommandsSize() { return m_historyCommands.size(); }

	void SetHistoryCommandsIndex(int index) { m_historyCommandsIndex = index; }
	int GetHistoryCommandsIndex() { return m_historyCommandsIndex; }

	void ClearHistory();

private:
	std::vector<std::string> m_history;
	std::vector<std::string> m_historyCommands;

	int m_historyCommandsIndex = 0;
};

