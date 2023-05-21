#include <vector>
#include <iostream>

#include <SFML/Graphics.hpp>
#include <array>
#include "Curve.h"


# define PI           3.14159265358979323846
//using precision = float;
//
//struct plot_params
//{
//	precision _min_range;
//	precision _max_range;
//	precision _step;
//};
//
//
//template <typename TFunction>
//auto plot(const plot_params pp, TFunction&& f)
//{
//
//	sf::VertexArray curve(sf::PrimitiveType::LineStrip,
//		std::ceil((pp._max_range - pp._min_range) / pp._step));
//
//	for (auto x = pp._min_range; x < pp._max_range; x += pp._step)
//	{
//		curve.append(sf::Vertex(f(x), sf::Color::Red));
//	}
//	return curve;
//}

int main()
{
	sf::Clock clock;

	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	int HEIGHT = 800;
	int WIDTH = 800;

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Curve", sf::Style::Default, settings);

	int w = 100;
	const int cols = WIDTH / w - 1;
	const int rows = HEIGHT / w - 1;
	int padding = 5;
	int r = (w - 2*padding) / 2;
	float angle_deg = 0;


	sf::CircleShape large_circle(r);
	large_circle.setOrigin(r, r);
	large_circle.setFillColor(sf::Color::Transparent);
	large_circle.setOutlineColor(sf::Color::White);
	large_circle.setOutlineThickness(-2.f);

	sf::CircleShape small_circle(5);
	small_circle.setOrigin(5, 5);
	small_circle.setFillColor(sf::Color::White);


	std::vector<std::vector<Curve>> curves(rows, std::vector<Curve>(cols));

	

	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		std::cout << 1.f / elapsed.asSeconds() << std::endl;



		if (angle_deg >= 359) {
			angle_deg = 0;

			for (int i = 0; i < rows; i++) {
				for (int j = 0; j < cols; j++) {
					curves[i][j].clear();
					
				}
			}

		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		/*const auto my_params = []
		{
			plot_params pp;
			pp._min_range = 0.f;
			pp._max_range = 200.f;
			pp._step = 0.1f;
			return pp;
		}();

		auto curve = plot(my_params,
			[](auto x) { return sf::Vector2f(x, 100-100*sin(0.1*x)); });
		window.draw(curve);
		window.display();*/

		window.clear(sf::Color::Black);
		

		// draw horizontal circles

		for (int j = 0; j < cols; j++) {	
			int cx = (j + 1) * w + w / 2;
			int cy = w / 2;
			large_circle.setPosition(cx, cy);
			window.draw(large_circle);


			int sx = cx + r * cos(angle_deg * (j+1) / 180.f * PI);
			int sy = cy + r * sin(angle_deg * (j+1) / 180.f * PI);
			small_circle.setPosition(sx, sy);
			window.draw(small_circle);


			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(sx, 0)),
				sf::Vertex(sf::Vector2f(sx, HEIGHT))
			};

			window.draw(line, 2, sf::Lines);



			for (int i = 0; i < rows; i++) {
				curves[i][j].setX(sx);
			}


		}


		// draw vertical circles

		for (int i = 0; i < rows; i++) {
			int cx = w / 2;
			int cy = (i + 1) * w + w / 2; 
			large_circle.setPosition(cx, cy);
			window.draw(large_circle);


			int sx = cx + r * cos(angle_deg * (i + 1) / 180.f * PI);
			int sy = cy + r * sin(angle_deg * (i + 1) / 180.f * PI);
			small_circle.setPosition(sx, sy);
			window.draw(small_circle);


			sf::Vertex line[] =
			{
				sf::Vertex(sf::Vector2f(0, sy)),
				sf::Vertex(sf::Vector2f(WIDTH, sy))
			};

			window.draw(line, 2, sf::Lines);


			for (int j = 0; j < cols; j++) {
				curves[i][j].setY(sy);
			}

		}
		


		for (int i = 0; i < rows; i++) {
			for (int j = 0; j < cols; j++) {
				curves[i][j].addPoint();
				sf::VertexArray path = curves[i][j].getCurve();
				size_t vertexCount = path.getVertexCount();

				window.draw(path);
				small_circle.setPosition( path[vertexCount-1].position );
				window.draw(small_circle);
			}
		}


		window.display();
		angle_deg+=36 * elapsed.asSeconds();

	}

	return 0;
}