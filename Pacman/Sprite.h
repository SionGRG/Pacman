#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__


#include "DataStructures.h"

class Animation;

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
	int Update(float& elapsedTime);
	int Terminate();

	SDL_Texture* GetTexture() { return m_Texture; }
	std::string_view GetSpriteName() { return m_SprData->Name; }
	SpriteData* GetSpriteData() { return m_SprData; }
	RECTF* GetSpritePosRect() { return &m_PosRect; }
	RECTF* GetTextureRect() { return &m_TexRect; }
	int DefineTextureRect(RECTF* texDim);
	int DefineTextureRect(int& frameIndex);

	bool m_Active = false;	// by default its asleep and should not render or update

private:
	SDL_Texture* m_Texture;			// Texture - SDL defined
	SpriteData* m_SprData;			// Data about the sprite from the json file
	Animation* m_Animation;			// Sprite animation
	RECTF m_PosRect;
	RECTF m_TexRect;

	bool m_Terminated = false;
};


#endif // !__SPRITE_H__