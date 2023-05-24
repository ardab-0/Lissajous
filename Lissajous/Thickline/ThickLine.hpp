#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class ThickLine {
public:
	ThickLine(std::vector<sf::Vector2f>& points, float thickness);
	sf::VertexArray getLine();

private:
	sf::VertexArray thickLine_;


};