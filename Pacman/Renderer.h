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
	SDL_Renderer* GetSDLRenderer() { return m_Renderer; }

	void RenderStaticText(std::string_view textData, std::string_view fontFile, int xPos = 0, int yPos = 0, int fontSize = 24, COLOUR rgbaColour = COLOUR(255, 225, 225, 255));
	void RenderText(std::string_view textData, std::string_view fontFile, int xPos = 0, int yPos = 0, int fontSize = 24, COLOUR rgbaColour = COLOUR(255, 225, 225, 255));

private:

	SDL_Window* m_Window;
	SDL_Renderer* m_Renderer;
	
	VTexts m_Texts;

	bool m_Terminated = false;

};


#endif // !__RENDERER_H__