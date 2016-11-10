#pragma once
#include "GameObject.h"
#include "Flame_Behaviour.h"

class Flame :
	public GameObject
{
private:
	Flame_Behaviour* m_Behaviour; // Behaviour component will calculate a circular path for the object.
	AWSprite* m_Sprite;
public:
	Flame(float x, float y, float radius); // Parameters required for movement.
	~Flame();

	void update();
	AWSprite* return_Sprite();
	bool is_Static();
	void draw();

};

