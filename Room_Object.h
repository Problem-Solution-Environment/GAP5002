#pragma once
#include "Room.h"
#include <vector>
#include "Bullet.h"
#include "Turret.h"

class Room_Object : public Room
{
private:
	std::vector<GameObject* > m_Actors;
public:
	Room_Object();
	void createObjects();
	void updateObjects();
	void drawObjects();
	void deleteObjects();
};