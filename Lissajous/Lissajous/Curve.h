#pragma once
#include <SFML/Graphics.hpp>

class Curve {

public:
	Curve();
	void addPoint();
	void setX(float x);
	void setY(float y);
	sf::VertexArray getCurve();
	void clear();


private:
	sf::VertexArray m_path;
	sf::Vector2f m_current;
};