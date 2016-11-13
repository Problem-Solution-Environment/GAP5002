#include "Flame.h"


Flame::Flame(float x, float y, float radius)
{
	m_Sprite = new AWSprite("images/flame.png", 3, 1);
	m_Sprite->set_world_position(x, y);
	m_Sprite->set_transparent_colour(0, 0, 0);
	m_Sprite->set_auto_animate(100);

	m_Behaviour = new Flame_Behaviour
	(
		x,
		y,
		radius
	);
}

Flame::~Flame()
{
}

void Flame::update()
{
	m_Behaviour->update(m_Sprite);
}

AWSprite* Flame::return_Sprite()
{
	return m_Sprite;
}

bool Flame::is_Static()
{
	return false;
}

void Flame::draw()
{
	m_Sprite->update_everything();
}
