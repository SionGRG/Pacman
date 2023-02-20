#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__


#include "DataStructures.h"

/*
	This class contains the structure of the sprite used in the game
	* It contains the data and methods of the Sprite 
*/
class Sprite
{
public:
	Sprite() {}
	Sprite(SpriteData* sprData, SDL_Texture* sprTex, int xPos, int yPos);
	~Sprite();
	
	int Init(int& xPos, int& yPos);
	int Update();
	int Terminate();

	SDL_Texture* GetTexture() { return m_Texture; }
	std::string_view GetSpriteName() { return m_SprData->Name; }
	SpriteData* GetSpriteData() { return m_SprData; }
	SDL_Rect* GetSpritePosRect() { return &m_PosRect; }

	bool m_Active = false;	// by default its asleep and should not render or update
private:

	SDL_Texture* m_Texture;
	SpriteData* m_SprData;				// Data about the sprite from the json file
	SDL_Rect m_PosRect;

	bool m_Terminated = false;
};


#endif // !__SPRITE_H__