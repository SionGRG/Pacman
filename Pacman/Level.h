#pragma once

#ifndef __LEVEL_H__
#define __LEVEL_H__

#include "DataStructures.h"


class ResourceCache;

/*
	This class contains the structure of level
	* It contains the data and methods of the level
*/

class Level
{
public:
	Level() {};
	virtual ~Level();

	virtual int Init() = 0;
	int Update(float& elapsedTime);
	virtual int Terminate();

	int AddGameObject(std::string_view objName, GameObject* gameObject);
	int RemoveGameObject(std::string_view objName);
	GameObject* GetGameObject(std::string_view objName);

	GameObjectMap* GetGameObjects() { return &m_GameObjects; };
	std::string_view GetName() { return m_Name; }

protected:
	std::string m_Name;

	ResourceCache* m_Cache;
	GameObjectMap m_GameObjects;

private:
	bool m_Terminated = false;
};


#endif // !__LEVEL_H__