#include "Turret.h"

Turret::Turret(std::vector<GameObject*> &actors, float x, float y)
{
	m_Sprite = new AWSprite("images/Turret.bmp", 1, 1);
	m_Sprite->set_world_position(x, y);

	m_Behaviour = new Turret_Behaviour(
		actors,
		x + (m_Sprite->get_width() / 2),
		y + (m_Sprite->get_height() / 2)
	);
}

Turret::~Turret()
{
	SAFE_DELETE_PTR(m_Behaviour);
	SAFE_DELETE_PTR(m_Sprite);
}

void Turret::update()
{
	m_Behaviour->checkTimer();
}

AWSprite* Turret::return_Sprite()
{
	return m_Sprite;
}


bool Turret::is_Static()
{
	return true;
}

void Turret::draw()
{
	m_Sprite->update_everything();
}