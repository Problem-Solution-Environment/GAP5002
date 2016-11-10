#pragma once
#include "GameObject.h"
#include "Turret_Behaviour.h"
#include <vector>

class Turret : public GameObject
{
private:
	Turret_Behaviour* m_Behaviour;
	AWSprite* m_Sprite;

	// REMOVED: 10/11 no longer needed to be stored in this class
	// as it is immediately handed off to the behaviour component
	// in the constructor
	//std::vector<GameObject* > m_Actors;

	// REMOVED: 10/11 not needed so far, possible unneeded at all
	//float m_XPos;
	//float m_YPos;

public:
	Turret(std::vector<GameObject* > &actors, float x, float y);
	// ADDED: 10/09 destructor
	~Turret();
	void update();
	AWSprite* return_Sprite();
	bool is_Static();
	void draw();

};