#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "GameObject.h"
#include "Sprite.h"

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
	AddGameObject("Playfield", new GameObject(new Sprite(m_Cache->GetSpriteData("Playfield"), m_Cache->GetTexture("Lv1Spritesheet"), 0, 0), true));
	AddGameObject("PackmanLeft", new GameObject(new Sprite(m_Cache->GetSpriteData("Pacman_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), 200, 200), true));
	AddGameObject("PackmanCRight", new GameObject(new Sprite(m_Cache->GetSpriteData("Pacman_right_32"), m_Cache->GetTexture("Lv1Spritesheet"), 100, 150), true));
	AddGameObject("RedGhost", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost1", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 120, 150), true));
	AddGameObject("RedGhost2", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 250, 150), true));
	AddGameObject("RedGhost3", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 150), true));
	AddGameObject("RedGhost4", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 360, 150), true));
	AddGameObject("RedGhost5", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 450), true));
	AddGameObject("RedGhost6", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 650), true));
	AddGameObject("RedGhost7", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost8", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 170, 350), true));
	AddGameObject("RedGhost9", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 180, 250), true));
	AddGameObject("RedGhost10", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 200, 550), true));
	AddGameObject("RedGhost11", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 500, 350), true));
	AddGameObject("RedGhost12", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 350), true));
	AddGameObject("RedGhost13", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 200), true));
	AddGameObject("RedGhost14", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 450, 100), true));
	AddGameObject("RedGhost15", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 320, 350), true));
	AddGameObject("RedGhost16", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 400, 250), true));
	AddGameObject("RedGhost17", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 460, 200), true));
	AddGameObject("RedGhost18", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 310, 170), true));
	AddGameObject("RedGhost19", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 030, 240), true));
	AddGameObject("RedGhost20", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 250, 300), true));


	return retCode;
}

int PacmanLv1::Terminate()
{



	m_Terminated = false;
	return retCode;
}
