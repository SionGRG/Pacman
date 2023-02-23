#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"


class ResourceCache;

class Player : public GameObject
{
public:
	Player(Sprite* spr, v2& pos, bool activate, ResourceCache* cache);
	~Player() override;

	int Init(Sprite* spr) override;
	int UpdateControls() override;
	int Terminate() override;

protected:
	int EnableSprite(std::string_view sprName);

private:
	ResourceCache* m_Cache;

	int m_Score;
	int m_Lives;

	bool m_Terminated = false;
};

#endif // !__PLAYER_H__