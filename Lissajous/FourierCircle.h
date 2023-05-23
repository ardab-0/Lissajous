#pragma once
#include <memory>
#include <SFML/Graphics.hpp>

class FourierCircle {
public:
	FourierCircle(sf::RenderWindow* window, float r, float f, sf::Vector2f position);
	FourierCircle(){};

	void addChild(std::shared_ptr<FourierCircle> child);
	void update(float dt);
	void draw();
	sf::Vector2f getEndpoint();
	sf::Vector2f getLastEndpoint();
	std::shared_ptr<FourierCircle> getChild();

private:
	void calculateEndpoint();


	std::shared_ptr<FourierCircle> child_m = nullptr;
	sf::CircleShape circle_m;
	sf::Vector2f position_m;
	sf::Vector2f endpoint_m;
	float r_m;
	float f_m;
	float angle_deg_m;
	sf::RenderWindow* window_m;
};