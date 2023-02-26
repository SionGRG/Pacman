#pragma once
#ifndef _PACMAN_LEVEL_1_H__
#define _PACMAN_LEVEL_1_H__

#include "Level.h"


class PacmanLv1: public Level
{
public:
	PacmanLv1(std::string_view levelName, ResourceCache* cache);
	~PacmanLv1();

	int Init() override;
	int Terminate() override;

	bool TileIsValid(int& x, int& y);

	void GetPath(int sourceX, int sourceY, int destX, int destY, MapTileList& tiles);

	MapTileList* GetMapTiles() { return &m_MapTiles; }

private:
	MapTile* GetTile(int sourceX, int sourceY);
	//bool SortFromGhostSpawn(MapTile* a, MapTile* b);
	bool Pathfind(MapTile* sourceTile, MapTile* destTile, MapTileList& tiles);
	bool ListDoesNotContain(MapTile* sourceTile, MapTileList& tiles);

	MapTileList m_MapTiles;

	bool m_Terminated = false;
};

#endif // !_PACMAN_LEVEL_1_H__