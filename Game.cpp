#include "Game.h"

Game::Game()
{

}

Game::~Game()
{

}

void Game::setUp()
{
	setBackground("images/sBgrd1.png");

	m_Room.push_back(new Room_Object);
}

void Game::logic()
{
	for (int i = 0; i < m_Room.size(); i++)
	{
		m_Room[i]->updateObjects();
	}

}

void Game::draw()
{
	for (int i = 0; i < m_Room.size(); i++)
	{
		m_Room[i]->drawObjects();
	}
}