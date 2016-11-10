#pragma once
#include "Room.h"
#include <vector>
#include "Bullet.h"
#include "Turret.h"
#include "Collider_Object.h"

class Room_Object : public Room
{
private:
	std::vector<GameObject* > m_Actors;
	std::vector<GameObject* >::iterator m_Iter;
public:
	Room_Object();
	void createObjects();
	void updateObjects();
	void drawObjects();
	void deleteObjects();
	void deleteElement(int element);

	void performCollisions();
};