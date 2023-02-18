#pragma once

#ifndef __GAME_H__
#define __GAME_H__

#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "pacman.h"
#include "drawer.h"
#include <assert.h>
#include <iostream>
#include <vector>
#include "DataStructures.h"

class Renderer;
class ResourceCache;

class Game
{
public:

	Game();
	~Game();

	int Init();
	int UpdateEvents();
	int Update();
	int Terminate();
	
	int AddGameObject(std::string& objName, GameObject* gameObject);
	int RemoveGameObject(std::string& objName);
	GameObject* GetGameObject(std::string& objName);


	bool Running() { return m_IsRunning; }

private:
	Renderer* m_Renderer;
	Pacman* m_Pacman;
	Drawer* m_Drawer;
	bool m_IsRunning;

	ResourceCache* m_Cache;

	GameObjectMap m_GameObjects;
	GameObject* obj;

	/* Initialise the Game FPS */
	const float k_FPS = 60.f;
	const float k_FrameDelay = 1000 / k_FPS;

};

#endif // !__GAME_H__
