#pragma once

class Room
{
public:
	// Initialises all of the objects used in the room
	virtual void createObjects() = 0;

	// Calls the update function on every object, call this inside game->logic()
	virtual void updateObjects() = 0;

	// Calls the draw function on every object, call inside game->draw()
	virtual void drawObjects() = 0;

	// Used to destroy any objects in the rooms memory
	virtual void deleteObjects() = 0;
};