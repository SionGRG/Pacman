#include "GameObject.h"
#include "Sprite.h"


GameObject::GameObject(Sprite* spr, bool activate = false)
	:m_Active(activate)
{
	m_PosVel = v2(0, 0);
	Init(spr);
}

GameObject::~GameObject()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int GameObject::Init(Sprite* spr)
{
	// Activate and add the first sprite to the sprite container
	AddSprite(spr, true);


	return retCode;
}

int GameObject::Update(float& elapsedTime)
{
	// Only update the Gameobjects that are active
	if (m_Active)
	{
		const Uint8* keystate = SDL_GetKeyboardState(NULL);

		SetPositionVelocity(v2(0.2f,0));
		if (keystate[SDL_SCANCODE_UP])
			UpdateDirection(v2(-1.f, 1.f));
		
		// update the Gameobject's sprites
		for (auto itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
		{
			if (itSpr->second->m_Active) // only the active ones
				itSpr->second->Update(elapsedTime, this);
		}
	}

	return retCode;
}

int GameObject::Terminate()
{
	// Clear sprite memory
	for (SpriteMap::iterator itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
	{
		itSpr->second->Terminate();
		itSpr->second = nullptr;
		free(itSpr->second);
	}
	m_Sprites.clear();

	m_Terminated = true;

	return retCode;
}

int GameObject::AddSprite(Sprite* spr, bool activate)
{
	// Add the sprite to the sprite container
	spr->m_Active = activate;
	m_Sprites.emplace(spr->GetSpriteName(), spr);

	return retCode;
}

int GameObject::RemoveSprite(Sprite* spr)
{
	// Remove the sprite from the sprite container
	SpriteMap::iterator it;
	it = m_Sprites.find(spr->GetSpriteName().data());
	free(it->second);	// clear sprite memory
	m_Sprites.erase(it);

	return retCode;
}

Sprite* GameObject::GetSprite(std::string_view sprName)
{
	return m_Sprites.at(sprName.data());
}
