#ifndef GAME_CONSTANTS_H
#define GAME_CONSTANTS_H

// Object Tags are held by the objects, similar to object ID though
// so maybe consider making obsolete
enum ObjectTag
{
	NON_COLLIDER,
	PROJECTILE,
	COLLIDER
};

// Each type of onject in the game should be represented by an object ID
// used in setting up each room as it will create objects based on what
// ID it recieves
enum OBJECT_ID
{
	TURRET_ID,
	COLLIDER_ID
};

#endif // !(GAME_CONSTANTS_H)

