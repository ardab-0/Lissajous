#include "FourierCircle.h"
# define PI           3.14159265358979323846


FourierCircle::FourierCircle(sf::RenderWindow* window, float r, float f, sf::Vector2f position)
{
	r_m = r;
	f_m = f;
	position_m = position;
	window_m = window;
	angle_deg_m = 0;

	calculateEndpoint();

	circle_m = sf::CircleShape(r);
	circle_m.setOrigin(r, r);
	circle_m.setPosition(position);
	circle_m.setFillColor(sf::Color::Transparent);
	circle_m.setOutlineColor(sf::Color::White);
	circle_m.setOutlineThickness(-2.f);

}

void FourierCircle::addChild(std::shared_ptr<FourierCircle> child)
{
	child_m = child;
	
}

void FourierCircle::update(float dt)
{	
	circle_m.setPosition(position_m);

	angle_deg_m += f_m * dt;

	if (angle_deg_m >= 359) {
		angle_deg_m = 0;
	}
	calculateEndpoint();
	if (child_m) {
		child_m->position_m = endpoint_m;
	}
}

void FourierCircle::draw()
{
	window_m->draw(circle_m);

	sf::Vertex line[] =
	{
		sf::Vertex(position_m),
		sf::Vertex(endpoint_m)
	};

	window_m->draw(line, 2, sf::Lines);
}

sf::Vector2f FourierCircle::getEndpoint()
{
	return endpoint_m;
}

sf::Vector2f FourierCircle::getLastEndpoint()
{
	if (child_m != nullptr) {
		return child_m->getLastEndpoint();
	}
	else{
		return endpoint_m;
	}
}

std::shared_ptr<FourierCircle> FourierCircle::getChild()
{
	return child_m;
}

void FourierCircle::calculateEndpoint()
{
	endpoint_m.x = position_m.x + r_m * cos(angle_deg_m / 180.f * PI);
	endpoint_m.y = position_m.y + r_m * sin(angle_deg_m / 180.f * PI);
}
