#include "Player.h"
#include "Sprite.h"
#include "ResourceCache.h"


Player::Player(Sprite* spr, v2& pos, bool activate, ResourceCache* cache)
	:m_Cache(cache)
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
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_right_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), false);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_up_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), false);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Pacman_down_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), false);

	return retCode;
}

int Player::UpdateControls()
{
	const Uint8* keystate = SDL_GetKeyboardState(NULL);

	if (keystate[SDL_SCANCODE_LEFT])
	{
		SetPositionVelocity(v2(0.5f, 0));
		UpdateDirection(v2(-1.f, 1.f));
		EnableSprite("Pacman_left_32");
	}
	else if (keystate[SDL_SCANCODE_RIGHT])
	{
		SetPositionVelocity(v2(0.5f, 0));
		UpdateDirection(v2(1.f, 1.f));
		EnableSprite("Pacman_right_32");
	}
	else if (keystate[SDL_SCANCODE_UP])
	{
		SetPositionVelocity(v2(0, 0.5f));
		UpdateDirection(v2(1.f, -1.f));
		EnableSprite("Pacman_up_32");
	}
	else if (keystate[SDL_SCANCODE_DOWN])
	{
		SetPositionVelocity(v2(0, 0.5f));
		UpdateDirection(v2(1.f, 1.f));
		EnableSprite("Pacman_down_32");
	}
	else
	{
		SetPositionVelocity(v2(0, 0));
	}

	return retCode;
}

int Player::Terminate()
{
	delete m_Cache;

	m_Terminated = true;

	return retCode;
}

int Player::EnableSprite(std::string_view sprName)
{
	// Disable all the sprite and enable the specified one
	for (SpriteMap::iterator itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
	{
		itSpr->second->m_Active = false;
	}
	m_Sprites.at(sprName.data())->m_Active = true;

	return retCode;
}

