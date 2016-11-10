#include "Room_Object.h"
Room_Object::Room_Object()
{
	createObjects();
}

void Room_Object::createObjects()
{
	m_Actors.push_back(new Turret(m_Actors, 200, 200));
}

void Room_Object::updateObjects()
{
	// Update every object in the vector
	for (int i = 0; i < m_Actors.size(); i++)
	{
		m_Actors[i]->update();
	}
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