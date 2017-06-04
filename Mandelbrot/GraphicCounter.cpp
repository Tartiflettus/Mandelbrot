#include "stdafx.h"
#include "GraphicCounter.h"
#include <string>
//#include <cassert>
//#include <Windows.h>

GraphicCounter::GraphicCounter(unsigned int cnt): m_counter(cnt)
{
	m_font.loadFromFile("MontereyFLF.ttf");
	setFont(m_font);

	setFillColor(sf::Color::Red);
	setCharacterSize(50);

	setCount(m_counter);
}


GraphicCounter::~GraphicCounter()
{
}

void GraphicCounter::setCount(unsigned int cnt)
{
	m_counter = cnt;
	setString(std::to_string(cnt));
}
