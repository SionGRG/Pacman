#include "Collider.h"
#include "GameObject.h"
#include "Sprite.h"

Collider2D::Collider2D(std::string_view name, bool collide, v2& cBoxSize, v2& sprPos, v2& sprPosVel)
	: m_Name(name), m_CollisionStatus(collide), m_CollisionBoxSize(cBoxSize)
{
	Init(sprPos, sprPosVel);
}

Collider2D::~Collider2D()
{
	if (!m_Terminated)
		Terminate();
}

int Collider2D::Init(v2& sprPos, v2& sprPosVel)
{
	/*posX*/
	m_CollisionBox2D.x = sprPos.myX - m_CollisionBoxSize.myX;
	/*posY*/
	m_CollisionBox2D.y = sprPos.myY - m_CollisionBoxSize.myY;
	/*width*/
	m_CollisionBox2D.w = m_CollisionBoxSize.myX;
	/*height*/
	m_CollisionBox2D.h = m_CollisionBoxSize.myY;
	/*velocity*/
	m_CollisionBox2D.velocity = sprPosVel;
	/*origin*/
	m_CollisionBox2D.origin = sprPos;
	return retCode;
}

int Collider2D::Update(GameObject* parentObj, Sprite* parentSpr)
{
	if (m_CollisionStatus)
	{
		// Update the collision box location
		m_CollisionBox2D.w = m_CollisionBoxSize.myX * parentSpr->GetScale().myX;
		m_CollisionBox2D.h = m_CollisionBoxSize.myY * parentSpr->GetScale().myY;
		m_CollisionBox2D.x = parentObj->GetPosition().myX - m_CollisionBox2D.w;
		m_CollisionBox2D.y = parentObj->GetPosition().myY - m_CollisionBox2D.h;
		m_CollisionBox2D.velocity = *parentObj->GetPositionVelocity();
		m_CollisionBox2D.origin = parentObj->GetPosition();
	}

	return retCode;
}

int Collider2D::Terminate()
{

	m_Terminated = true;
	return retCode;
}

// Check collision between the collision box and a point
bool Collider2D::PointCollision(const v2& vPoint)
{
	// No collision if the collsion box is not enabled
	if (m_CollisionStatus == false)
		return false;
	else
		return (vPoint.myX >= m_CollisionBox2D.origin.myX - m_CollisionBox2D.w / 2 && 
				vPoint.myY >= m_CollisionBox2D.origin.myY - m_CollisionBox2D.h / 2 &&
				vPoint.myX < m_CollisionBox2D.origin.myX + m_CollisionBox2D.w / 2 && 
				vPoint.myY < m_CollisionBox2D.origin.myY + m_CollisionBox2D.h / 2);
}

// Check collision between the collision box and another rect
bool Collider2D::BoxCollision(const RECTB& rTarget)
{
	// No collision if the collsion box is not enabled
	if (m_CollisionStatus == false)
		return false;
	else
		return (rTarget.origin.myX - rTarget.w / 2 < m_CollisionBox2D.origin.myX + m_CollisionBox2D.w / 2 &&
				rTarget.origin.myX - rTarget.w / 2 + rTarget.w > m_CollisionBox2D.origin.myX - m_CollisionBox2D.w / 2 &&
				rTarget.origin.myY - rTarget.h / 2 < m_CollisionBox2D.origin.myY + m_CollisionBox2D.h / 2 &&
				rTarget.origin.myY - rTarget.h / 2 + rTarget.h > m_CollisionBox2D.origin.myY - m_CollisionBox2D.h / 2);
}
