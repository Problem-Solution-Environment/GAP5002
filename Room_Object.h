#pragma once
#include "Room.h"
#include <vector>
#include <map>
#include "Bullet.h"
#include "Turret.h"
#include "Collider_Object.h"
#include "GAME_CONSTANTS.h"
#include "Vector2.h"


class Room_Object : public Room
{
private:
	std::vector<GameObject* > m_Actors;
	std::vector<GameObject* >::iterator m_Iter;
public:
	Room_Object(std::multimap<OBJECT_ID, Vector2> data);

	// ADDED: 12/09 destructor to safely delete all the objects
	// managed by this room
	~Room_Object();
	void createObjects();
	void updateObjects();
	void drawObjects();
	void deleteObjects();

	// Pops an item in position n from the vector
	void deleteElement(int element);

	void performCollisions();
};