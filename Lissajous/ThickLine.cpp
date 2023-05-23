#include "ThickLine.hpp"
#include <math.h>


sf::Vector2f normalized(sf::Vector2f vec) {

	return vec / sqrt(vec.x * vec.x + vec.y * vec.y);
}


float dot(sf::Vector2f v1, sf::Vector2f v2) {
	return v1.x * v2.x + v1.y * v2.y;
}



ThickLine::ThickLine(std::vector<sf::Vector2f>& points, float thickness)
{
	thickLine_ = sf::VertexArray(sf::TriangleStrip, points.size() * 2);


	for (size_t i = 0; i < points.size() - 1; i++) {
		

		sf::Vector2f line = points[i+1] - points[i];
		sf::Vector2f normal = normalized( sf::Vector2f(-line.y, line.x) );


		sf::Vector2f a = points[i] - thickness * normal;
		sf::Vector2f b = points[i] + thickness * normal;
		sf::Vector2f c = points[i+1] - thickness * normal;
		sf::Vector2f d = points[i+1] + thickness * normal;


		if (i == 0) {
			thickLine_[0] = a;
			thickLine_[1] = b;
		}
		if (i == points.size() - 2) {
			thickLine_[(i + 1) * 2] = c;
			thickLine_[(i + 1) * 2 + 1] = d;
			continue;
		}

		sf::Vector2f tangent = normalized(normalized(points[i+2] - points[i+1]) + normalized(points[i+1] - points[i]));
		sf::Vector2f miter = sf::Vector2f(-tangent.y, tangent.x); //normal of the tangent


		float length = thickness / dot(miter, normal);

		sf::Vector2f m1 = points[i+1] - length * miter;
		sf::Vector2f m2 = points[i+1] + length * miter;

		
		
		thickLine_[(i+1)*2 ] = m1;
		thickLine_[(i+1)*2 + 1] = m2;
		

	}

}

sf::VertexArray ThickLine::getLine()
{
	return thickLine_;
}



