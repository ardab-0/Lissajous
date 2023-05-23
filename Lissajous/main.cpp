#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <array>
#include "Curve.h"
#include "ThickLine.hpp"
#include "LissajousCurve.h"
#include "Fourier.h"


int main()
{
	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	int HEIGHT = 800;
	int WIDTH = 1600;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Curve", sf::Style::Default, settings);

	LissajousCurve lissajous(&window, 100, 72);
	

	Fourier fourier(&window, 10, 200, 36, sf::Vector2f(400, 400));

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		std::cout << 1.f / elapsed.asSeconds() << std::endl;



		
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		window.clear(sf::Color::Black);
		

		//lissajous.update(elapsed.asSeconds());

		fourier.update(elapsed.asSeconds());
		fourier.draw();

		/*std::vector<sf::Vector2f> p = { {10, 10}, {100, 200}, {200, 0}, {300, 100} };

		ThickLine line(p, 5);
		window.draw(line.getLine());*/

		window.display();
		

	}

	return 0;
}