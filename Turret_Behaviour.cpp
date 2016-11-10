#include "Turret_Behaviour.h"
#include "Bullet.h"     // include Bullet to create the bullets


Turret_Behaviour::Turret_Behaviour(std::vector<GameObject* > &actors, float x, float y) : m_Actors(actors)
{

	m_XPos = x;
	m_YPos = y;

	m_Timer = new Timer;
	m_Timer->startTimer();
}

void Turret_Behaviour::checkTimer()
{
	if (m_Timer)
	{
		// If the timer has passed a certain point
		if (m_Timer->getElapsedTime() > FIRE_INTERVAL)
		{
			// Fire and restart the timer at zero
			fire();

			m_Timer->resetTimer();
			m_Timer->startTimer();
		}
	}

}

void Turret_Behaviour::fire()
{
	for (int i = 0; i < DIRECTION_SWITCH; i++)
	{
		// Fire a bullet in all 4 directions
		m_Actors.push_back(new Bullet(m_XPos, m_YPos, i));
	}

}
