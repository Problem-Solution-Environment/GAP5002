#pragma once
#include "AWSprite.h"
#include <cmath>

class Flame_Behaviour
{
private:
	float m_xPos;
	float m_yPos;
	float m_Radius;
	float m_Angle;
public:
	Flame_Behaviour(float x, float y, float radius);
	~Flame_Behaviour();

	void update(AWSprite *aws);
};

