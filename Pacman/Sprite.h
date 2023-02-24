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
	Sprite(SpriteData* sprData, SDL_Texture* sprTex, v2& pos);
	~Sprite();
	
	int Init();
	int Update(float& elapsedTime, GameObject* parent);
	int Terminate();

	SDL_Texture* GetTexture() { return m_Texture; }
	std::string_view GetSpriteName() { return m_SprData->Name; }
	SpriteData* GetSpriteData() { return m_SprData; }
	RECTF* GetTextureRect() { return &m_TexRect; }
	int DefineTextureRect(RECTF* texDim);
	int DefineTextureRect(int& frameIndex);

	RECTF* GetPosRect() { return &m_PosRect; }
	v2& GetPos() { return m_Pos; }

	bool m_Active = false;	// by default its asleep and should not render or update

private:
	SDL_Texture* m_Texture;			// Texture - SDL defined
	SpriteData* m_SprData;			// Data about the sprite from the json file
	Animation* m_Animation;			// Sprite animation
	RECTF m_TexRect;
	
	v2 m_Pos;
	v2 m_Scale;
	RECTF m_PosRect;

	bool m_Terminated = false;
};


#endif // !__SPRITE_H__