#include "Room_Object.h"
Room_Object::Room_Object()
{
	createObjects();
}

void Room_Object::createObjects()
{
	m_Actors.push_back(new Turret(m_Actors, 200, 200));
	m_Actors.push_back(new Collider_Object(400, 200));
	
}

void Room_Object::updateObjects()
{
	// Update every object in the vector
	for (int i = 0; i < m_Actors.size(); i++)
	{
		m_Actors[i]->update();
		if (m_Actors[i]->return_Sprite()->is_on_screen() == false)
		{
			deleteElement(i);
		}
	}

	// Perform collisions
	performCollisions();
}

void Room_Object::drawObjects()
{
	// Draw every item in the vector
	for (int i = 0; i < m_Actors.size(); i++)
	{
		m_Actors[i]->draw();
	}
}

void Room_Object::deleteObjects()
{
}

void Room_Object::deleteElement(int element)
{
	delete m_Actors[element];
	m_Actors.erase(m_Actors.begin() + element);
}

void Room_Object::performCollisions()
{
	for (int i = 0; i < m_Actors.size(); i++)
	{
		for (int j = 0; j < m_Actors.size(); j++)
		{
			if (m_Actors[i] != m_Actors[j] && m_Actors[i]->return_Sprite()->bb_collision(m_Actors[j]->return_Sprite()))
			{
				if (!m_Actors[i]->is_Static())
				{
					deleteElement(i);
				}
				else
				{
					deleteElement(j);
				}
			}
		}
	}
}
