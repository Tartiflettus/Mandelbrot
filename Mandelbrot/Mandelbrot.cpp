#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <complex>
#include "MandelbrotSet.h"
#include "MandelbrotMath.h"
#include "GraphicCounter.h"
#include <iostream>

int main()
{
	MandelbrotSet<float> set(1024, 0);
	GraphicCounter cnt;
	cnt.setPosition(0, 0);
	sf::RenderWindow window(sf::VideoMode(1024, 768), "Mandelbrot");

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				switch (event.key.code) {
					case sf::Keyboard::Up:
						set.nextIteration();
						cnt.setCount(set.getLastIteration());
						break;
					case sf::Keyboard::Left:
						set.nextIteration(50);
						cnt.setCount(set.getLastIteration());
						break;
					case sf::Keyboard::Right:
						set.nextIteration(set.getLastIteration() * 2);
						cnt.setCount(set.getLastIteration());
						break;
				}
			}
		}

		window.clear();
		window.draw(set);
		window.draw(cnt);
		window.display();
		sf::sleep(sf::milliseconds(50));
	}

	using stype = float;
	using type = std::complex<stype>;

	//test isInSet
	type c = 0;
	assert(isInSet(c));
	assert(!isInSet(c + 5.f));

	//test nextOfMandelbrotSequence
	c = type(-1.f, 0.f);
	assert(isInSet(c));
	assert(Mandelbrot_n(0u, type(-1.f, 0.f)) == type(0.f));
	assert(std::abs(Mandelbrot_n(5u, type(-1.f, 0.f))) <= 2.f);

	//test physicalToMath
	assert(physicalToMath(std::complex<float>(1, 1), 2, 2) == -0.5f);


	//std::cout << "OK\n";
	//getchar();
	return 0;
}

