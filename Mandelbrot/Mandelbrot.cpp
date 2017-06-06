#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <cassert>
#include <complex>
#include "MandelbrotSet.h"
#include "MandelbrotMath.h"
#include "GraphicCounter.h"
#include <iostream>

#include "Parallel.h"
#include "ParalMandelbrotSet.h"

#include <memory> //pointeurs intelligents


void main_asserts();


int main(int argc, char **argv)
{
	std::unique_ptr<MandelbrotSet<float>> setPtr;
	if (argc == 2 && std::string(argv[1]) == "-p") { //parallèle
		setPtr.reset(new ParalMandelbrotSet<float>(1024, 0));
	}
	else {
		setPtr.reset(new MandelbrotSet<float>(1024, 0)); //normal
	}

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
						setPtr->nextIteration();
						cnt.setCount(setPtr->getLastIteration());
						break;
					case sf::Keyboard::Left:
						setPtr->nextIteration(50);
						cnt.setCount(setPtr->getLastIteration());
						break;
					case sf::Keyboard::Right:
						setPtr->nextIteration(setPtr->getLastIteration());
						cnt.setCount(setPtr->getLastIteration());
						break;
				}
			}
		}

		window.clear();
		window.draw(*setPtr);
		window.draw(cnt);
		window.display();
		sf::sleep(sf::milliseconds(50));
	}


	#ifndef NDEBUG
		main_asserts();
	#endif // !NDEBUG


	return 0;
}


void main_asserts() {
	assert(false);
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

	//test du module de parallelisation
	constexpr size_t N = (1 << 24) + 1;
	auto t = std::make_unique<bool[]>(N);
	std::fill(t.get(), t.get()+N, false);
	parallelFor(0, N, [&t](int i) {
	t[i] = true;
	});
	for (int i = 0; i < N; ++i) {
	assert(t[i]);
	}

	//test de ParalMandelbrotSet
	ParalMandelbrotSet<float> testset(1024, 0);

	std::cout << "OK\n";
	getchar();
}

