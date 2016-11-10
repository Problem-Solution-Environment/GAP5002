#include "Game.h"
#include <iostream>

using namespace std;

int main(int argc, char* argv[])
{
	GameBase::initSDL(640, 480);
	Game *game = new Game();

	game->setUp();
	game->start();

	SAFE_DELETE_PTR(game);

	return 0;
}