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
	int UpdateEvents();
	int Update();
	int Terminate();
	
	bool Running() { return m_IsRunning; }

private:
	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	Pacman* m_Pacman;
	Drawer* m_Drawer;
	bool m_IsRunning;

	/* Initialise the Game FPS */
	const float k_FPS = 60.f;
	const float k_FrameDelay = 1000 / k_FPS;

};

#endif // !__GAME_H__
