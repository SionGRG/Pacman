#include <algorithm>
#include "Player.h"
#include "Sprite.h"
#include "Animation.h"
#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "Collider.h"

Player::Player(Sprite* spr, v2& pos, bool activate, ResourceCache* cache, PacmanLv1* level)
	:m_Cache(cache), m_Level(level)
{
	m_Active = activate;
	m_Pos = pos;
	Init(spr);
}

Player::~Player()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int Player::Init(Sprite* spr)
{
	// Activate and add the first sprite to the sprite container
	GameObject::Init(spr);

	// Add the other sprites to the sprite container
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_right_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0), true), false);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_up_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0), true), false);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_down_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0), true), false);

	// Set the player data
	m_MoveSpeed = 0.7f;
	m_Blocked = 1.f;
	m_Lives = 3;
	m_Score = 0;

	return retCode;
}

int Player::UpdateControls(float& elapsedTime)
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT])
	{
		SetPositionVelocity(v2(m_MoveSpeed, 0));
		UpdateDirection(v2(-1.f * m_Blocked, 1.f));
		EnableSprite("Pacman_left_32");
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		SetPositionVelocity(v2(m_MoveSpeed, 0));
		UpdateDirection(v2(1.f * m_Blocked, 1.f));
		EnableSprite("Pacman_right_32");
	}
	else if (keystate[SDL_SCANCODE_UP])
	{
		SetPositionVelocity(v2(0, m_MoveSpeed));
		UpdateDirection(v2(1.f, -1.f * m_Blocked));
		EnableSprite("Pacman_up_32");
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		SetPositionVelocity(v2(0, m_MoveSpeed));
		UpdateDirection(v2(1.f, 1.f * m_Blocked));
		EnableSprite("Pacman_down_32");
	}
	else
	{
		SetPositionVelocity(v2(0, 0));
		StopAnimations();
	}

	return retCode;
}

int Player::UpdateCollision(float& elapsedTime)
{
	std::for_each(m_Level->GetGameObjects()->begin(), m_Level->GetGameObjects()->end(),[this](std::pair<const std::string, GameObject*> objPair)
		{
			if (objPair.second->m_Active)
			{
				if (objPair.second->GetType() == "Dot")
				{
					if (HasCollided(objPair.second->GetPosition()))
					{
						IncreaseScore();
						objPair.second->m_Active = false;
					}
				}
				if (objPair.second->GetType() == "BigDot")
				{
					if (HasCollided(objPair.second->GetPosition()))
					{
						IncreaseMoveSpeed();
						objPair.second->m_Active = false;
					}
				}
			}
		});


	std::for_each(m_Level->GetMapTiles()->begin(), m_Level->GetMapTiles()->end(), [this](MapTile* tile)
		{
			if (tile->m_IsBlockingFlag)
			{
				for (SpriteMap::iterator itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
				{
					if (!itSpr->second->GetBoxCollider()->PointCollision(v2(tile->m_X, tile->m_Y)))
						m_Blocked = 1.f;
					else 
						m_Blocked = -1.f;
				}
			}
		});

	return retCode;
}

int Player::Terminate()
{
	delete m_Cache;

	m_Terminated = true;

	return retCode;
}

