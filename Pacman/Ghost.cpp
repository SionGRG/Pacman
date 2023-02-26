#include "Ghost.h"
#include "Sprite.h"
#include "ResourceCache.h"
#include "PacmanLv1.h"

Ghost::Ghost(Sprite* spr, v2& pos, bool activate, ResourceCache* cache, PacmanLv1* level)
	: m_Cache(cache), m_Level(level)
{
	m_Active = activate;
	m_Pos = pos;
	Init(spr);
}

Ghost::~Ghost()
{
	if (!m_Terminated)
		Terminate();
}

int Ghost::Init(Sprite* spr)
{
	GameObject::Init(spr);

	// Add the vulnerable and dead ghost sprites to the sprite container
	AddSprite(new Sprite(m_Cache->GetSpriteData("Ghost_Vulnerable_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), false);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Ghost_Dead_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), false);

	// Initialise the sprite status
	m_IsVulnerableFlag = false;
	m_IsDeadFlag = false;

	// Initialise tile positions
	m_CurrentTileX = m_NextTileX = GetPosition().myX / 22;
	m_CurrentTileY = m_NextTileY = GetPosition().myY / 22;

	return retCode;
}

int Ghost::UpdateControls(float& elapsedTime)
{
	// Update Ghost status
	if (m_IsDeadFlag)	// Dead
		EnableSprite("Ghost_Dead_32");
	else if (m_IsVulnerableFlag)	// Vulnerable
		EnableSprite("Ghost_Vulnerable_32");
	else
		EnableSprite(m_Sprites.begin()->first);

	// Update Ghost movement
	float speed = 30.f;
	int nextTileX = GetCurrentTileX() + m_DesiredMovementX;
	int nextTileY = GetCurrentTileY() + m_DesiredMovementY;

	if (m_IsDeadFlag)
		speed = 120.f;

	if (IsAtDestination())
	{
		if (!m_Path.empty())
		{
			MapTile* nextTile = m_Path.front();
			m_Path.pop_front();
			SetNextTile(nextTile->m_X, nextTile->m_Y);
		}
		else if (m_Level->TileIsValid(nextTileX, nextTileY))
		{
			SetNextTile(nextTileX, nextTileY);
		}
		else
		{
			if (m_DesiredMovementX == 1)
			{
				m_DesiredMovementX = 0;
				m_DesiredMovementY = 1;
			}
			else if (m_DesiredMovementY == 1)
			{
				m_DesiredMovementX = -1;
				m_DesiredMovementY = 0;
			}
			else if (m_DesiredMovementX == -1)
			{
				m_DesiredMovementX = 0;
				m_DesiredMovementY = -1;
			}
			else
			{
				m_DesiredMovementX = 1;
				m_DesiredMovementY = 0;
			}

			m_IsDeadFlag = false;
		}
	}

	int tileSize = 22;
	Vector2f destination(m_NextTileX * tileSize, m_NextTileY * tileSize);
	Vector2f direction = destination - GetPosition();

	float distanceToMove = elapsedTime * speed;

	if (distanceToMove > direction.Length())
	{
		//SetPositionVelocity(destination);
		SetPosition(destination);
		m_CurrentTileX = m_NextTileX;
		m_CurrentTileY = m_NextTileY;
	}
	else
	{
		direction.Normalize();
		v2 vel = direction * distanceToMove;
		//UpdatePositionVelocity(vel);
		SetPosition(vel);
	}

	return retCode;
}

int Ghost::Terminate()
{
	delete m_Cache;
	delete m_Level;

	m_Terminated = true;
	return retCode;
}

void Ghost::SetNextTile(int& x, int& y)
{
	m_NextTileX = x;
	m_NextTileY = y;
}

bool Ghost::IsAtDestination()
{
	if (m_CurrentTileX == m_NextTileX && m_CurrentTileY == m_NextTileY)
	{
		return true;
	}

	return false;
}

int Ghost::Die()
{
	m_Path.clear();
	m_Level->GetPath(m_CurrentTileX, m_CurrentTileY, 13, 13, m_Path);
	return retCode;
}
