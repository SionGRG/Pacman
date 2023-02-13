
#include "Game.h"

int main(int argc, char **argv)
{
	Game* game = new Game();

	if (game->Init() != retCode)
	{
		assert(0 && "Failed to initialize Game");
		exit(errCode);
	}

	if (game->Update() != retCode)
	{
		assert(0 && "Failed to Run the Game loop");
		exit(errCode);
	}

	return 0;
}

