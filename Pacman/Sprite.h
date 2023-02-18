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
	Sprite(std::string& sprName, SDL_Texture* sprTex);
	~Sprite();
	
	int Init();
	int Update();
	int Terminate();

	SDL_Texture* GetTexture() { return m_Texture; }
	std::string& GetSpriteName() { return m_Name; }

	bool m_Active = false;	// by default its asleep and should not render or update
private:
	std::string m_Name;

	SDL_Texture* m_Texture;

	bool m_Terminated = false;
};


#endif // !__SPRITE_H__