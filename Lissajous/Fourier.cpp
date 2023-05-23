#include "Fourier.h"


Fourier::Fourier(sf::RenderWindow* window, int n, float r, float f, sf::Vector2f origin) 
{
	window_m = window;
	n_m = n;
	r_m = r;
	f_m = f;
	origin_m = origin;
	path_m = sf::VertexArray(sf::LineStrip);
	numberPrevSamples_m = 2000;
	speedX_m = 30; // pixel/s

	samplingInterval_m = 0.01;
	secondsSincePrevSample_m = 0;

	lastPoint_m = sf::Vector2f(origin.x + window->getSize().x / 4, origin.y);

	lastPointCircle_m = sf::CircleShape(5);
	lastPointCircle_m.setOrigin(5, 5);
	lastPointCircle_m.setFillColor(sf::Color::White);
	lastPointCircle_m.setPosition(lastPoint_m);

	if (n > 0) {
		fourierCircle_m = std::make_shared<FourierCircle>(window, r, f, origin);
	}

	std::shared_ptr<FourierCircle> currentFourierCircle = fourierCircle_m;

	for (int i = 1; i < n; i++) {
		auto child_origin = currentFourierCircle->getEndpoint();
		float child_f = f * (2 * i + 1);
		float child_r = r / (2 * i + 1);
		currentFourierCircle->addChild(std::make_shared<FourierCircle>(window, child_r, child_f, child_origin));
		currentFourierCircle = currentFourierCircle->getChild();
	}
}

void Fourier::update(float dt)
{
	std::shared_ptr<FourierCircle> currentFourierCircle = fourierCircle_m;

	while (currentFourierCircle != nullptr) {
		currentFourierCircle->update(dt);
		currentFourierCircle = currentFourierCircle->getChild();
	}

	lastPoint_m.y = fourierCircle_m->getLastEndpoint().y;
	lastPointCircle_m.setPosition(lastPoint_m);
	
	if (secondsSincePrevSample_m >= samplingInterval_m) {
		if (previousYPoints_m.size() >= numberPrevSamples_m) {
			previousYPoints_m.pop_front();
		}
		previousYPoints_m.push_back(lastPoint_m.y);
		secondsSincePrevSample_m = 0;
	}
	secondsSincePrevSample_m += dt;

	path_m.clear();
	fillVertexArray();

}

void Fourier::draw()
{
	std::shared_ptr<FourierCircle> currentFourierCircle = fourierCircle_m;

	while (currentFourierCircle != nullptr) {
		currentFourierCircle->draw();
		currentFourierCircle = currentFourierCircle->getChild();
	}

	window_m->draw(lastPointCircle_m);

	window_m->draw(path_m);
}

void Fourier::fillVertexArray()
{	
	float initialX = lastPoint_m.x;
	float currentX = initialX;

	for (auto it = previousYPoints_m.crbegin(); it != previousYPoints_m.crend(); it++)
	{	
		float val = *it;
		path_m.append(sf::Vector2f(currentX, *it));
		currentX += speedX_m * samplingInterval_m;
	}

}
