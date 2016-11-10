#pragma once
#include "GameObject.h"

class Collider_Object : public GameObject
{
private:
	AWSprite* m_Sprite;

public:
	Collider_Object(float x, float y);

	AWSprite* return_Sprite();
	bool is_Static();
	void update();
	void draw();	
};