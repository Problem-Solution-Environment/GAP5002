#pragma once
#include "GameBase.h"
#include <vector>
#include "Room_Object.h"

class Game :
	public GameBase
{
private:
	std::vector<Room* > m_Room;
	//std::vector<GameObject* > m_Actors;
	//std::vector<GameObject* >::iterator m_ActorIt;
	
public:
	Game();
	~Game();
	void setUp();
	void logic();
	void draw();
};

