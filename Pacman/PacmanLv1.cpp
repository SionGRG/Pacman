#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"

PacmanLv1::PacmanLv1(std::string_view levelName, ResourceCache* cache)
{
	m_Name = levelName;
	m_Cache = cache;
	Init();
}

PacmanLv1::~PacmanLv1()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int PacmanLv1::Init()
{
	// add test game objects
	AddGameObject("Playfield", new GameObject(new Sprite(m_Cache->GetSpriteData("Playfield"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(0, 0), true));
	AddGameObject("Packman", new Player(new Sprite(m_Cache->GetSpriteData("Pacman_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 100)), v2(0, 0), true, m_Cache));
	AddGameObject("RedGhost", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(150, 150), true));


	return retCode;
}

int PacmanLv1::Terminate()
{



	m_Terminated = false;
	return retCode;
}
