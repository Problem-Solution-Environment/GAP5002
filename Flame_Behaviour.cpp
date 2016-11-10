#include "Flame_Behaviour.h"



Flame_Behaviour::Flame_Behaviour(float x, float y, float radius)
{
	m_xPos = x;
	m_yPos = y;
	m_Radius = radius;
	m_Angle = 0;
}

void Flame_Behaviour::update(AWSprite *aws)
{
	if (m_Angle < 360)
	{
		m_Angle += 0.005;
	}
	else if (m_Angle == 360)
	{
		m_Angle = 0;
	}

	aws->set_world_position
	(
		m_xPos + cos(m_Angle) * m_Radius,
		m_yPos + sin(m_Angle) * m_Radius
	);
}

Flame_Behaviour::~Flame_Behaviour()
{
}
