#pragma once

#ifndef __GHOST_H__
#define __GHOST_H__

#include "GameObject.h"

class ResourceCache;
class PacmanLv1;

class Ghost : public GameObject
{
public:
	Ghost(Sprite* spr, v2& pos, bool activate, ResourceCache* cache, PacmanLv1* level);
	~Ghost() override;

	int Init(Sprite* spr) override;
	int UpdateControls(float& elapsedTime) override;
	int Terminate() override;

	std::string_view GetType() override { return "Ghost"; }; // by default its "GameObject"

	void SetNextTile(int& x, int& y);
	int GetCurrentTileX() const { return m_CurrentTileX; }
	int GetCurrentTileY() const { return m_CurrentTileY; }

	bool IsAtDestination();
	bool IsVulnerable() { return m_IsVulnerableFlag; }
	bool IsDead() { return m_IsDeadFlag; }

	int Die();

protected:
	ResourceCache* m_Cache;

	int m_CurrentTileX;
	int m_CurrentTileY;

	int m_NextTileX;
	int m_NextTileY;

	bool m_IsVulnerableFlag;
	bool m_IsDeadFlag;

	MapTileList m_Path;

private:
	PacmanLv1* m_Level;

	int m_DesiredMovementX;
	int m_DesiredMovementY;

	bool m_Terminated = false;
};

#endif // !__GHOST_H__