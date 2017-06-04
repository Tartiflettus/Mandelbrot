#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <complex>
#include "MandelbrotSet.h"
#include "MandelbrotMath.h"
#include <iostream>

int main()
{
	MandelbrotSet set(1024, 10);
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
		}

		window.clear();
		window.draw(set);
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


	std::cout << "OK\n";
	getchar();
	return 0;
}

