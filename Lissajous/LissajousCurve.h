#pragma once
#include <SFML/Graphics.hpp>
#include "Curve.h"
class LissajousCurve {

public:
	LissajousCurve(sf::RenderWindow* window, int cellWidth, int speed);
	void update(float dt);


private:
	std::vector<std::vector<Curve>> curves_m;
	sf::CircleShape large_circle_m;
	sf::CircleShape small_circle_m;
	float angle_deg_m;
	int rows_m;
	int cols_m;
	int cellWidth_m;
	sf::RenderWindow* window_m;
	int r_m;
	int height_m;
	int width_m;
	int speed_m;
};