#pragma once

#include <SFML\Graphics.hpp>

class GraphicCounter : public sf::Text
{
private:
	sf::Font m_font;
	unsigned int m_counter;

public:
	GraphicCounter(unsigned int cnt = 0);
	~GraphicCounter();

	void setCount(unsigned int cnt);
};

