#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "assert.h"
#include "pacman.h"
#include "drawer.h"
#include <iostream>

#define retCode 0
#define errCode -1

class Game
{
public:

	Game();
	~Game();

	int Init();
	int Update();
	int Terminate();
	
private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Pacman* m_Pacman;
	Drawer* m_Drawer;

};

#endif // !__GAME_H__
