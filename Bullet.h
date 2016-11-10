#pragma once
#include "GameObject.h"

// Velocity applied in given direction
const float SPEED = 10.0f;
const float FIRE_OFFSET = 32.0f;

class Bullet : public GameObject
{
private:
	AWSprite* m_Sprite;

public:
	// CHANGED: 10/11 removed the two velocity parameters and replaced
	// them with an int instead, velocity is determined in the constructor
	// using a switch (possibly convert to enum?)
	Bullet(float x, float y, int direction);

	// Required interface functions
	AWSprite* return_Sprite();
	bool is_Static(); // inline?
	void update();
	void draw();
};