#pragma once
#include "GameBase.h"
#include <map>
#include "Vector2.h"
#include "Room_Object.h"
#include "GAME_CONSTANTS.h"

class Game :
	public GameBase
{
private:
	// CHANGED: 12/09 originally a vector, switched to simply
	// a pointer as only one room needs to be created at a time
	Room* m_Room;

	// ADDED: 12/09 int that represents room number (possible swap
	// to enum), multimap to hold object data for room
	int m_Current_Room;
	std::multimap<OBJECT_ID, Vector2> m_Room_Data;

	//std::vector<GameObject* > m_Actors;
	//std::vector<GameObject* >::iterator m_ActorIt;
	
public:
	Game();
	~Game();
	void setUp();
	void onKeyPressed();
	void logic();
	void draw();

	// Each function here holds explicit definitions of object positions in the room
	// look for better alternative. (Factory pattern?)
	void room01_Create();
	void room02_Create();

	// Switch statetment handles calling create room function
	void switch_Room();
};

