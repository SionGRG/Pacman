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
	GameObject(Sprite* spr, v2& pos, bool activate);
	virtual ~GameObject();

	virtual int Init(Sprite* spr);
	virtual int UpdateControls() { return retCode; }
	virtual int Update(float& elapsedTime);
	virtual int UpdateCollision(float& elapsedTime) { return retCode; }
	virtual int Terminate();

	// Sprite Functions
	SpriteMap* GetSprites() { return &m_Sprites; }
	int AddSprite(Sprite* spr, bool activate);
	int RemoveSprite(Sprite* spr);
	Sprite* GetSprite(std::string_view sprName);

	// Movement
	v2 GetPosition();
	v2* GetPositionVelocity() { return &m_PosVel; }
	void SetPositionVelocity(v2& vel) { m_PosVel = vel; }
	void UpdatePositionVelocity(v2& vel) { m_PosVel += vel; }
	void UpdateDirection(v2& vel) { m_PosVel *= vel; }

	// Collisions
	bool HasCollided(const v2& position);

	bool m_Active = false ;	// by default its asleep and should not render or update
	int m_Type = 0;	// by default its "GameObject"
	virtual std::string_view GetType() { return "GameObject"; }; // by default its "GameObject"

protected:
	std::string m_Name;
	SpriteMap m_Sprites;

	v2 m_Pos;
	v2 m_PosVel;

private:
	bool m_Terminated = false;
};

#endif // !__GAMEOBJECT_H__