#include "Bullet.h"

Bullet::Bullet(float x, float y, int direction)
{
	m_Sprite = new AWSprite("images/Bullet.bmp", 1, 1);
	m_Sprite->set_auto_move(SPEED);

	// Switch that applies a velocity to a bullet depending on the int direction
	// consider swapping for an enumerated type
	switch (direction)
	{
	case 0:
		m_Sprite->set_velocities(-SPEED, 0); // LEFT
		m_Sprite->set_world_position(x - FIRE_OFFSET, y);
		break;

	case 1:
		m_Sprite->set_velocities(0, -SPEED); // UP
		m_Sprite->set_world_position(x, y - FIRE_OFFSET);
		break;

	case 2:
		m_Sprite->set_velocities(SPEED, 0); // RIGHT
		m_Sprite->set_world_position(x + FIRE_OFFSET, y);
		break;

	case 3:
		m_Sprite->set_velocities(0, SPEED); // DOWN
		m_Sprite->set_world_position(x, y + FIRE_OFFSET);
		break;
	}
}

AWSprite* Bullet::return_Sprite()
{
	return m_Sprite;
}

bool Bullet::is_Static()
{
	return false;
}

void Bullet::update()
{

}

void Bullet::draw()
{
	m_Sprite->update_everything();
}