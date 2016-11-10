#pragma once
#include "AWSprite.h"

class GameObject : public AWSprite
{
public:
	// gets the AWSprite in use by this class for collision checking
	virtual AWSprite* return_Sprite() = 0;

	// Used for efficient collision checking
	virtual bool is_Static() = 0;

	// ADDED: 10/11 allows the actors vector to update each object 
	// in the Logic() loop
	// Ensures the object is updated each frame
	virtual void update() = 0;

	// ADDED: 10/11 allows the actors vector to draw the object every
	// frame
	// Ensures the object is drawn each frame
	virtual void draw() = 0;
};
