#pragma once
#ifndef __GAMEOBJECT_H__
#define __GAMEOBJECT_H__

#include "DataStructures.h"

class Sprite;

/*
	This class contains the structure of the game object 
	* It contains the data and methods of the game object
*/
class GameObject
{
public:
	GameObject() {}
	GameObject(Sprite* spr, bool activate);
	virtual ~GameObject();

	int Init(Sprite* spr);
	int Update(float& elapsedTime);
	int Terminate();

	SpriteMap* GetSprites() { return &m_Sprites; }

	// Sprite Functions
	int AddSprite(Sprite* spr, bool activate);
	int RemoveSprite(Sprite* spr);
	Sprite* GetSprite(std::string_view sprName);
	

	bool m_Active = false ;	// by default its asleep and should not render or update
private:
	std::string m_Name;

	SpriteMap m_Sprites;

	bool m_Terminated = false;
};

#endif // !__GAMEOBJECT_H__