#include "Level.h"
#include "ResourceCache.h"
#include "GameObject.h"


Level::~Level()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int Level::Update(float& elapsedTime)
{

	// Update the game objects
	for (auto itObj = m_GameObjects.begin(); itObj != m_GameObjects.end(); ++itObj)
	{
		itObj->second->Update(elapsedTime);
	}
	
	return retCode;
}

int Level::Terminate()
{
	delete m_Cache;

	// Terminate the game objects
	for (auto itObj = m_GameObjects.begin(); itObj != m_GameObjects.end(); ++itObj)
	{
		itObj->second->Terminate();
		delete itObj->second;
	}
	m_GameObjects.clear();

	m_Terminated = true;

	return retCode;
}

int Level::AddGameObject(std::string_view objName, GameObject* gameObject)
{
	// insert the game object into the storage	
	m_GameObjects.emplace(objName, gameObject);
	return retCode;
}

int Level::RemoveGameObject(std::string_view objName)
{
	// Remove the game object
	GameObjectMap::iterator it;
	it = m_GameObjects.find(objName.data());
	delete it->second;
	m_GameObjects.erase(it);

	return retCode;
}

GameObject* Level::GetGameObject(std::string_view objName)
{
	// Retun the game object
	return m_GameObjects.at(objName.data());
}