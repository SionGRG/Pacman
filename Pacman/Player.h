#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "GameObject.h"


class ResourceCache;
class Level;

class Player : public GameObject
{
public:
	Player(Sprite* spr, v2& pos, bool activate, ResourceCache* cache, Level* level);
	~Player() override;

	int Init(Sprite* spr) override;
	int UpdateControls() override;
	int UpdateCollision(float& elapsedTime) override;
	int Terminate() override;

	void IncreaseScore() { m_Score++; }
	void IncreaseMoveSpeed() { m_MoveSpeed = 1.2f; }
	int GetScore() { return m_Score; }
	int GetLives() { return m_Lives; }

protected:
	int EnableSprite(std::string_view sprName);
	int StopAnimations();

private:
	ResourceCache* m_Cache;
	Level* m_Level;

	int m_Score;
	int m_Lives;
	float m_MoveSpeed;

	bool m_Terminated = false;
};

#endif // !__PLAYER_H__