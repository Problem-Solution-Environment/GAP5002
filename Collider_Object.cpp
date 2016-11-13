#include "Collider_Object.h"

Collider_Object::Collider_Object(float x, float y)
{
	m_Sprite = new AWSprite("images/Collider.bmp", 1, 1);
	m_Sprite->set_world_position(x, y);
	m_Angle = 0;
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
	m_Angle += 0.5f;
}

void Collider_Object::draw()
{
	m_Sprite->rotateAndDraw(m_Angle, 10, 10);
	//m_Sprite->update_everything();

}
