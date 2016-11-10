#pragma once
#include "timer.h"
#include <vector>
#include "GameObject.h"

using namespace timer;

const float FIRE_INTERVAL = 2.0f;
const int DIRECTION_SWITCH = 4;

class Turret_Behaviour
{
private:
	Timer* m_Timer;
	std::vector<GameObject* > &m_Actors;
	float m_XPos;
	float m_YPos;

public:
	Turret_Behaviour(std::vector<GameObject* > &actors, float x, float y);

	void checkTimer();
	void fire();
};
