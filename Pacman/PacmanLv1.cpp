#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include "Ghost.h"
#include "Dot.h"
#include "BigDot.h"


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
	AddGameObject("Dot", new Dot(new Sprite(m_Cache->GetSpriteData("Dot_Small_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(300, 150), true));
	AddGameObject("BigDot", new BigDot(new Sprite(m_Cache->GetSpriteData("Dot_Big_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(260, 150), true));
	AddGameObject("Packman", new Player(new Sprite(m_Cache->GetSpriteData("Pacman_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(498, 540), true, m_Cache));
	AddGameObject("RedGhost", new Ghost(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(498, 350), true, m_Cache));


	return retCode;
}

int PacmanLv1::Terminate()
{



	m_Terminated = false;
	return retCode;
}
