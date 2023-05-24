#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "FourierCircle.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include <queue>

class Fourier {
public:
	Fourier(sf::RenderWindow* window, int n, float r, float f, sf::Vector2f origin);
	void update(float dt);
	void draw();
private:
	void fillVertexArray();


	int n_m;
	std::shared_ptr<FourierCircle> fourierCircle_m;
	sf::RenderWindow* window_m;
	float r_m;
	float f_m;
	sf::Vector2f origin_m;
	sf::Vector2f lastPoint_m;
	sf::CircleShape lastPointCircle_m;
	std::deque<float> previousYPoints_m;
	float samplingInterval_m;
	float secondsSincePrevSample_m;
	int numberPrevSamples_m;
	sf::VertexArray path_m;
	float speedX_m;
	
};