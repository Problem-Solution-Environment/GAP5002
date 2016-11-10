#pragma once
#include <cmath>

class Vector2
{
	float m_x;
	float m_y;
public:

	Vector2(float x, float y)
		: m_x(x), m_y(y) {}

	float getX() { return this->m_x; }
	float getY() { return this->m_y; }

	float magnitude()
	{
		return sqrt(m_x * m_x + m_y * m_y);
	}

	void normalize()
	{
		this->m_x /= this->magnitude();
		this->m_y /= this->magnitude();
	}

	Vector2 operator-(Vector2 &v2) const
	{
		return Vector2
		(
			this->m_x - v2.m_x,
			this->m_y - v2.m_y
		);
	}
};