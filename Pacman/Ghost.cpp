#include "Ghost.h"
#include "Sprite.h"
#include "ResourceCache.h"

Ghost::Ghost(Sprite* spr, v2& pos, bool activate, ResourceCache* cache)
	: m_Cache(cache)
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
	AddSprite(new Sprite(m_Cache->GetSpriteData("Ghost_Vulnerable_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(30, 0)), true);
	AddSprite(new Sprite(m_Cache->GetSpriteData("Ghost_Dead_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(-30, 0)), true);

	return retCode;
}

int Ghost::UpdateControls()
{

	return retCode;
}

int Ghost::Terminate()
{
	delete m_Cache;

	m_Terminated = true;
	return retCode;
}
