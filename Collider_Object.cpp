#include "Collider_Object.h"

Collider_Object::Collider_Object(float x, float y)
{
	m_Sprite = new AWSprite("images/Collider.bmp", 1, 1);
	m_Sprite->set_world_position(x, y);
}

AWSprite * Collider_Object::return_Sprite()
{
	return m_Sprite;
}

bool Collider_Object::is_Static()
{
	return true;
}

void Collider_Object::update()
{

}

void Collider_Object::draw()
{
	m_Sprite->update_everything();
}
