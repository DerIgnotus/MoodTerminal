#pragma once

#include <SFML/Graphics.hpp>

class History
{
public:
	History();
	void AddToHistory(const std::string& command);
	void ClearHistory();
	std::vector<std::string> GetHistory() const { return m_history; }
	int GetHistorySize() { return m_history.size(); }

private:
	std::vector<std::string> m_history;
};

