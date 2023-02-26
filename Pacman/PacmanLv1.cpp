#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include "Ghost.h"
#include "Dot.h"
#include "BigDot.h"
#include <fstream>
#include <algorithm>


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
	AddGameObject("1Playfield", new GameObject(new Sprite(m_Cache->GetSpriteData("Playfield"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(0, 0), true));

	// Load the map data and initialize the gameobjects, check World class from old Pacman
	std::string mapData;
	std::ifstream mapFile ("map.txt");

	if (mapFile.is_open())
	{
		int lineIndex = 0;
		int dotIndex = 0;
		int bigDotIndex = 0;
		int mapStartPosX = 220;
		int mapStartPosY = 60;

		while (!mapFile.eof())
		{
			std::getline(mapFile, mapData);

			for (int i = 0; i < mapData.length(); i++)
			{
				// Initialise the map of the level
				MapTile* tile = new MapTile(i + mapStartPosX, lineIndex + mapStartPosY, (mapData[i] == 'x'));
				m_MapTiles.emplace_back(tile);

				// Initialise the Dot gameobjects based on the map data
				if (mapData[i] == '.')
				{
					AddGameObject("Dot" + std::to_string(dotIndex), new Dot(new Sprite(m_Cache->GetSpriteData("Dot_Small_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2((i*22) + mapStartPosX, (lineIndex*22) + mapStartPosY), true));
					++dotIndex;
				}

				// Initialise the Big Dot gameobjects based on the map data
				if (mapData[i] == 'o')
				{
					AddGameObject("BigDot" + std::to_string(bigDotIndex), new BigDot(new Sprite(m_Cache->GetSpriteData("Dot_Big_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2((i*22) + mapStartPosX, (lineIndex*22) + mapStartPosY), true));
					++bigDotIndex;
				}

				// add the player's gameobject
				if (mapData[i] == 'p')
				{
					AddGameObject("Packman", new Player(new Sprite(m_Cache->GetSpriteData("Pacman_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2((i * 22) + mapStartPosX, (lineIndex * 22) + mapStartPosY), true, m_Cache, this));
				}
			}
			++lineIndex;
		}
	}

	// add test game objects
	AddGameObject("RedGhost", new Ghost(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(498, 350), true, m_Cache));


	return retCode;
}

int PacmanLv1::Terminate()
{
	std::for_each(m_MapTiles.begin(), m_MapTiles.end(), [](MapTile* tile) {
		delete tile;
		});
	m_MapTiles.clear();

	m_Terminated = false;
	return retCode;
}

bool PacmanLv1::TileIsValid(int& x, int& y)
{
	bool valid = false;
	std::for_each(m_MapTiles.begin(), m_MapTiles.end(), [&valid, &x, &y](MapTile* tile) 
		{
			if (x == tile->m_X && y == tile->m_Y && !tile->m_IsBlockingFlag)
				valid = true;
		});

	return valid;
}

bool PacmanLv1::HasIntersectedDot(const v2& position)
{
	bool intersected = false;
	std::for_each(m_GameObjects.begin(), m_GameObjects.end(), [&intersected, &position](std::pair<const std::string, GameObject*> objPair)
		{
			if ((objPair.second->GetPosition() - position).Length() < 5.f)
			{
				intersected = true;
			}
		});

	return intersected;
}

bool PacmanLv1::HasIntersectedBigDot(const v2& position)
{
	return false;
}

bool PacmanLv1::HasIntersectedCherry(const v2& position)
{
	return false;
}

void PacmanLv1::GetPath(int& sourceX, int& sourceY, int& destX, int& destY, MapTileVector& tiles)
{
}

MapTile* PacmanLv1::GetTile(int& aFromX, int& aFromY)
{
	return nullptr;
}

bool PacmanLv1::Pathfind(MapTile* sourceTile, MapTile* destTile, MapTileVector& tiles)
{
	return false;
}

bool PacmanLv1::ListDoesNotContain(MapTile* sourceTile, MapTileVector& tiles)
{
	return false;
}
