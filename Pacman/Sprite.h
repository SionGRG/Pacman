#pragma once
#ifndef __SPRITE_H__
#define __SPRITE_H__



#include "SDL.h"
#include "DataStructures.h"


class TextureCache;


class Sprite
{
public:
	Sprite() {}
	Sprite(std::string& sprName, TextureCache* sprTex);
	~Sprite();
	
	int Init();
	int Update();
	int Terminate();

	SDL_Texture* GetTexture();

	std::string& GetSpriteName() { return m_Name; }

	bool m_Active = false;	// by default its asleep and should not render or update
private:
	std::string m_Name;

	TextureCache* m_Texture;

	bool m_Terminated = false;
};


#endif // !__SPRITE_H__