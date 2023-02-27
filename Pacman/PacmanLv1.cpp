#include "PacmanLv1.h"
#include "ResourceCache.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Sprite.h"
#include "Player.h"
#include "Ghost.h"
#include "Dot.h"
#include "BigDot.h"
#include <fstream>
#include <algorithm>

PacmanLv1::PacmanLv1(std::string_view levelName, ResourceCache* cache, Renderer* renderer)
{
	m_Name = levelName;
	m_Cache = cache;
	m_Renderer = renderer;
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
					AddGameObject("Pacman", new Player(new Sprite(m_Cache->GetSpriteData("Pacman_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0), true), v2((i * 22) + mapStartPosX, (lineIndex * 22) + mapStartPosY), true, m_Cache, this));
				}
			}
			++lineIndex;
		}
	}

	// add test game objects
	AddGameObject("RedGhost", new Ghost(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), v2(0, 0)), v2(498, 350), true, m_Cache, this));

	m_Renderer->RenderStaticText("Score: ", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 50);
	m_Renderer->RenderStaticText("Lives: ", "freefont-ttf\\sfd\\FreeMono.ttf", 20, 80);
	m_Renderer->RenderStaticText("FPS: ", "freefont-ttf\\sfd\\FreeMono.ttf", 850, 50);
	return retCode;
}

int PacmanLv1::Update(float& elapsedTime)
{
	Level::Update(elapsedTime);

	return retCode;
}

int PacmanLv1::RenderText()
{
	if (m_GameObjects.at("Pacman")->GetType() == "Player")
	{
		Player* p = (Player*)m_GameObjects.at("Pacman");

		m_Renderer->RenderText(std::to_string(p->GetScore()).c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 110, 50);
		m_Renderer->RenderText(std::to_string(p->GetLives()).c_str(), "freefont-ttf\\sfd\\FreeMono.ttf", 110, 80);
	}

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

void PacmanLv1::GetPath(int sourceX, int sourceY, int destX, int destY, MapTileList& tiles)
{
	MapTile* sourceTile = GetTile(sourceX, sourceY);
	MapTile* destTile = GetTile(destX, destY);

	for (MapTileList::iterator itTiles = m_MapTiles.begin(); itTiles != m_MapTiles.end(); itTiles++)
	{
		MapTile* tile = *itTiles;
		tile->m_IsVisitedFlag = false;
	}

	Pathfind(sourceTile, destTile, tiles);
}

MapTile* PacmanLv1::GetTile(int sourceX, int sourceY)
{
	for (MapTileList::iterator itTile = m_MapTiles.begin(); itTile != m_MapTiles.end(); ++itTile)
	{
		MapTile* tile = *itTile;
		if (tile->m_X == sourceX && tile->m_Y == sourceY)
		{
			return tile;
		}
	}

	return nullptr;
}

bool SortFromGhostSpawn(MapTile* a, MapTile* b)
{
	int la = abs(a->m_X - 13) + abs(a->m_Y - 13);
	int lb = abs(b->m_X - 13) + abs(b->m_Y - 13);

	return la < lb;
}

bool PacmanLv1::Pathfind(MapTile* sourceTile, MapTile* destTile, MapTileList& tiles)
{
	sourceTile->m_IsVisitedFlag = true;

	if (sourceTile->m_IsBlockingFlag)
		return false;

	if (sourceTile == destTile)
		return true;

	MapTileList neighborList;

	MapTile* up = GetTile(sourceTile->m_X, sourceTile->m_Y - 1);
	if (up && !up->m_IsVisitedFlag && !up->m_IsBlockingFlag && ListDoesNotContain(up, tiles))
		neighborList.push_front(up);

	MapTile* down = GetTile(sourceTile->m_X, sourceTile->m_Y + 1);
	if (down && !down->m_IsVisitedFlag && !down->m_IsBlockingFlag && ListDoesNotContain(down, tiles))
		neighborList.push_front(down);

	MapTile* right = GetTile(sourceTile->m_X + 1, sourceTile->m_Y);
	if (right && !right->m_IsVisitedFlag && !right->m_IsBlockingFlag && ListDoesNotContain(right, tiles))
		neighborList.push_front(right);

	MapTile* left = GetTile(sourceTile->m_X - 1, sourceTile->m_Y);
	if (left && !left->m_IsVisitedFlag && !left->m_IsBlockingFlag && ListDoesNotContain(left, tiles))
		neighborList.push_front(left);

	neighborList.sort(SortFromGhostSpawn);

	for (MapTileList::iterator list_iter = neighborList.begin(); list_iter != neighborList.end(); list_iter++)
	{
		MapTile* tile = *list_iter;

		tiles.push_back(tile);

		if (Pathfind(tile, destTile, tiles))
			return true;

		tiles.pop_back();
	}

	return false;
}

bool PacmanLv1::ListDoesNotContain(MapTile* sourceTile, MapTileList& tiles)
{
	for (MapTileList::iterator itTile = tiles.begin(); itTile != tiles.end(); itTile++)
	{
		MapTile* tile = *itTile;
		if (tile == sourceTile)
		{
			return false;
		}
	}

	return false;
}

