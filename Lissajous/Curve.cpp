#include "Curve.h"

Curve::Curve()
{
	m_path = sf::VertexArray(sf::LineStrip);
	m_current = sf::Vector2f();

}

void Curve::addPoint()
{
	m_path.append(m_current);
}

void Curve::setX(float x)
{
	m_current.x = x;
}

void Curve::setY(float y)
{
	m_current.y = y;
}

sf::VertexArray Curve::getCurve()
{
	return m_path;
}

void Curve::clear()
{
	m_path.clear();
}
