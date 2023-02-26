#pragma once

#ifndef __COLLIDER_H__
#define __COLLIDER_H__

#include "DataStructures.h"

class Collider2D
{
public:
	Collider2D(std::string_view name, bool collide, v2& cBoxSize, v2& sprPos, v2& sprPosVel);
	~Collider2D();
	
	int Init(v2& sprPos, v2& sprPosVel);
	int Update(GameObject* parentObj, Sprite* parentSpr);
	int Terminate();

	// Get functions
	bool* GetCollisionStatus() { return &m_CollisionStatus; }
	RECTB* GetCollisionBox() { return &m_CollisionBox2D; }

	// Set functions
	void SetCollisionStatus(bool ColStatus) { m_CollisionStatus = ColStatus; }
	void SetCollisionBox(RECTB& colRect) { m_CollisionBox2D = colRect; }

	// Collision functions
	bool PointCollision(const v2& vPoint);
	bool BoxCollision(const RECTB& rTarget);
private:
	std::string		m_Name;
	bool			m_CollisionStatus;		// Enabled = true, and disabled = false
	RECTB			m_CollisionBox2D;
	v2				m_CollisionBoxSize;
	bool			m_Terminated = false;
};


#endif // !__COLLIDER_H__