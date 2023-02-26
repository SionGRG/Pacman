#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"


class ResourceCache;
class PacmanLv1;

class Player : public GameObject
{
public:
	Player(Sprite* spr, v2& pos, bool activate, ResourceCache* cache, PacmanLv1* level);
	~Player() override;

	int Init(Sprite* spr) override;
	int UpdateControls(float& elapsedTime) override;
	int UpdateCollision(float& elapsedTime) override;
	int Terminate() override;

	void IncreaseScore() { m_Score++; }
	void IncreaseMoveSpeed() { m_MoveSpeed = 1.2f; }
	int GetScore() { return m_Score; }
	int GetLives() { return m_Lives; }

private:
	ResourceCache* m_Cache;
	PacmanLv1* m_Level;

	int m_Score;
	int m_Lives;
	float m_MoveSpeed;
	float m_Blocked;

	bool m_Terminated = false;
};

#endif // !__PLAYER_H__