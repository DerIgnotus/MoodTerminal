#pragma once

#include <SFML/Graphics.hpp>

class History
{
public:
	History();
	void AddToHistory(const std::string& command);
	std::vector<std::string> GetHistory() const { return m_history; }

private:
	std::vector<std::string> m_history;

};

