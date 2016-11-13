#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::setUp()
{
	setBackground("images/Room01.bmp");

	m_Room = NULL;

	//m_Room_Data = new std::multimap<OBJECT_ID, Vector2>;

	m_Current_Room = 1;
	switch_Room();
}

void Game::onKeyPressed()
{
	if (keyDown == SDLK_SPACE)
	{
		if (m_Current_Room == 1)
		{
			setBackground("images/Room02.bmp");
			m_Current_Room = 2;
			switch_Room();
		}
		else
		{
			setBackground("images/Room01.bmp");
			m_Current_Room = 1;
			switch_Room();
		}
	}
}

void Game::logic()
{
	m_Room->updateObjects();

}

void Game::draw()
{
	m_Room->drawObjects();
}

void Game::room01_Create()
{
	m_Room_Data.clear();

	m_Room_Data.insert(std::pair<OBJECT_ID, Vector2>(TURRET_ID, Vector2(100, 100)));
	m_Room_Data.insert(std::pair<OBJECT_ID, Vector2>(TURRET_ID, Vector2(400, 400)));	

	if (!m_Room)
	{
		m_Room = new Room_Object(m_Room_Data);
	}

}

void Game::room02_Create()
{
	m_Room_Data.clear();

	m_Room_Data.insert(std::pair<OBJECT_ID, Vector2>(TURRET_ID, Vector2(200, 200)));
	m_Room_Data.insert(std::pair<OBJECT_ID, Vector2>(COLLIDER_ID, Vector2(500, 400)));

	if (!m_Room)
	{
		m_Room = new Room_Object(m_Room_Data);
	}
}

void Game::switch_Room()
{
	switch (m_Current_Room)
	{
	case 1:
		if (m_Room)
		{
			SAFE_DELETE_PTR( m_Room);			
		}
		room01_Create();
		break;

	case 2:
		if (m_Room)
		{
			SAFE_DELETE_PTR(m_Room);
		}
		room02_Create();
		break;
	}

}
