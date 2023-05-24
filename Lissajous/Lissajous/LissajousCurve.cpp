#include "LissajousCurve.h"
# define PI           3.14159265358979323846


LissajousCurve::LissajousCurve(sf::RenderWindow* window, int cellWidth, int speed)
{
	cellWidth_m = cellWidth;
	window_m = window;
	speed_m = speed;
	width_m = window->getSize().x;
	height_m = window->getSize().y;
	cols_m = width_m / cellWidth - 1;
	rows_m = height_m / cellWidth - 1;
	int padding = 5;
	r_m = (cellWidth - 2 * padding) / 2;
	angle_deg_m = 0;


	large_circle_m = sf::CircleShape(r_m);
	large_circle_m.setOrigin(r_m, r_m);
	large_circle_m.setFillColor(sf::Color::Transparent);
	large_circle_m.setOutlineColor(sf::Color::White);
	large_circle_m.setOutlineThickness(-2.f);

	small_circle_m = sf::CircleShape(5);
	small_circle_m.setOrigin(5, 5);
	small_circle_m.setFillColor(sf::Color::White);


	curves_m = std::vector<std::vector<Curve>>(rows_m, std::vector<Curve>(cols_m));
}

void LissajousCurve::update(float dt)
{
	if (angle_deg_m >= 359) {
		angle_deg_m = 0;

		for (int i = 0; i < rows_m; i++) {
			for (int j = 0; j < cols_m; j++) {
				curves_m[i][j].clear();

			}
		}

	}



	// draw horizontal circles

	for (int j = 0; j < cols_m; j++) {
		int cx = (j + 1) * cellWidth_m + cellWidth_m / 2;
		int cy = cellWidth_m / 2;
		large_circle_m.setPosition(cx, cy);
		window_m->draw(large_circle_m);


		int sx = cx + r_m * cos(angle_deg_m * (j + 1) / 180.f * PI);
		int sy = cy + r_m * sin(angle_deg_m * (j + 1) / 180.f * PI);
		small_circle_m.setRadius(5);
		small_circle_m.setOrigin(5, 5);
		small_circle_m.setPosition(sx, sy);
		window_m ->draw(small_circle_m);


		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(sx, 0)),
			sf::Vertex(sf::Vector2f(sx, height_m))
		};

		window_m->draw(line, 2, sf::Lines);



		for (int i = 0; i < rows_m; i++) {
			curves_m[i][j].setX(sx);
		}


	}


	// draw vertical circles

	for (int i = 0; i < rows_m; i++) {
		int cx = cellWidth_m / 2;
		int cy = (i + 1) * cellWidth_m + cellWidth_m / 2;
		large_circle_m.setPosition(cx, cy);
		window_m->draw(large_circle_m);


		int sx = cx + r_m * cos(angle_deg_m * (i + 1) / 180.f * PI);
		int sy = cy + r_m * sin(angle_deg_m * (i + 1) / 180.f * PI);
		small_circle_m.setRadius(5);
		small_circle_m.setPosition(sx, sy);
		small_circle_m.setOrigin(5, 5);
		window_m->draw(small_circle_m);


		sf::Vertex line[] =
		{
			sf::Vertex(sf::Vector2f(0, sy)),
			sf::Vertex(sf::Vector2f(width_m, sy))
		};

		window_m->draw(line, 2, sf::Lines);


		for (int j = 0; j < cols_m; j++) {
			curves_m[i][j].setY(sy);
		}

	}



	for (int i = 0; i < rows_m; i++) {
		for (int j = 0; j < cols_m; j++) {
			curves_m[i][j].addPoint();
			sf::VertexArray path = curves_m[i][j].getCurve();
			size_t vertexCount = path.getVertexCount();

			window_m->draw(path);
			small_circle_m.setRadius(3);
			small_circle_m.setOrigin(3, 3);
			small_circle_m.setPosition(path[vertexCount - 1].position);
			window_m->draw(small_circle_m);
		}
	}

	angle_deg_m += speed_m * dt;

}
