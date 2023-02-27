#pragma once

#ifndef __TEXT_H__
#define __TEXT_H__


#include "DataStructures.h"
#include "SDL_ttf.h"


class Text
{
public:
	Text(SDL_Renderer* renderer, std::string_view text, std::string_view fontFile, int xPos, int yPos, int FontSize, COLOUR rgbaColour);
	~Text();

	int Init(int& xPos, int& yPos);
	int Render();
	int Terminate();

private:
	std::string m_TextData;
	const char* m_FontFile;

	SDL_Color m_Colour;
	SDL_Rect m_Position;
	TTF_Font* m_Font;
	int m_FontSize;

	SDL_Renderer* m_Renderer;
	SDL_Surface* m_Surface;
	SDL_Texture* m_Texture;

	bool m_Terminated = false;
};

#endif // !__TEXT_H__