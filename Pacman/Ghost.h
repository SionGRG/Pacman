#pragma once

#ifndef __GHOST_H__
#define __GHOST_H__

#include "GameObject.h"

class ResourceCache;

class Ghost : public GameObject
{
public:
	Ghost(Sprite* spr, v2& pos, bool activate, ResourceCache* cache);
	~Ghost() override;

	int Init(Sprite* spr) override;
	int UpdateControls() override;
	int Terminate() override;

	int m_Type = 2;
	std::string_view GetType() override { return "Ghost"; }; // by default its "GameObject"

protected:
	ResourceCache* m_Cache;

private:


	bool m_Terminated = false;
};

#endif // !__GHOST_H__