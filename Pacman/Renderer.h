#pragma once
#ifndef __RENDERER_H__
#define __RENDERER_H__


#include "SDL.h"
#include <vector>
#include "DataStructures.h"

class Renderer
{
public:
	Renderer() = delete;
	Renderer(const char* gameName);
	~Renderer();

	int Init(const char* gameName);
	//int Render(std::vector<GameObject*>& gameObjects);
	int Render(GameObjectMap* gameObjects);
	int Terminate();

	SDL_Window* GetWindow() { return m_Window; }
	SDL_Renderer* GetRenderer() { return m_Renderer; }
private:

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	
	bool m_Terminated = false;

};


#endif // !__RENDERER_H__