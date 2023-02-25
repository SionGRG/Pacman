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

private:
	MapTileVector m_MapTiles;

	bool m_Terminated = false;
};

#endif // !_PACMAN_LEVEL_1_H__