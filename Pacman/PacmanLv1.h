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

	bool HasIntersectedDot(const v2& position);
	bool HasIntersectedBigDot(const v2& position);
	bool HasIntersectedCherry(const v2& position);
	void GetPath(int& sourceX, int& sourceY, int& destX, int& destY, MapTileVector& tiles);

private:
	MapTile* GetTile(int& aFromX, int& aFromY);
	bool Pathfind(MapTile* sourceTile, MapTile* destTile, MapTileVector& tiles);
	bool ListDoesNotContain(MapTile* sourceTile, MapTileVector& tiles);
	
	MapTileVector m_MapTiles;

	bool m_Terminated = false;
};

#endif // !_PACMAN_LEVEL_1_H__