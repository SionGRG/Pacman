#include "GameObject.h"
#include "Sprite.h"
#include "Animation.h"


GameObject::GameObject(Sprite* spr, v2& pos = v2(0, 0), bool activate = false)
	:m_Active(activate), m_Pos(pos)
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
		// update the Gameobject's controlls
		UpdateControls(elapsedTime);
		
		// update the Gameobject's sprites
		for (auto itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
		{
			if (itSpr->second->m_Active) // only the active ones
			{
				itSpr->second->Update(elapsedTime, this);
			}
			
			// Update the position of the sprites, even if they are not active
			itSpr->second->GetPosRect()->x += m_PosVel.myX;
			itSpr->second->GetPosRect()->y += m_PosVel.myY;
		}

		// Update the game collisions
		UpdateCollision(elapsedTime);
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
		delete itSpr->second;
	}
	m_Sprites.clear();

	m_Terminated = true;

	return retCode;
}

int GameObject::AddSprite(Sprite* spr, bool activate)
{
	// Add the sprite to the sprite container
	spr->m_Active = activate;

	// Relate the position of the sprite to it's parent gameobject
	spr->GetPosRect()->x += m_Pos.myX;
	spr->GetPosRect()->y += m_Pos.myY;

	m_Sprites.emplace(spr->GetSpriteName(), spr);

	return retCode;
}

int GameObject::RemoveSprite(Sprite* spr)
{
	// Remove the sprite from the sprite container
	SpriteMap::iterator it;
	it = m_Sprites.find(spr->GetSpriteName().data());
	delete it->second;	// clear sprite memory
	m_Sprites.erase(it);

	return retCode;
}

Sprite* GameObject::GetSprite(std::string_view sprName)
{
	return m_Sprites.at(sprName.data());
}

v2 GameObject::GetPosition()
{
	return v2(
		m_Sprites.begin()->second->GetPosRect()->x,
		m_Sprites.begin()->second->GetPosRect()->y
	);
}

void GameObject::SetPosition(v2& vel)
{
	for (auto itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
	{
		itSpr->second->GetPosRect()->x = vel.myX;
		itSpr->second->GetPosRect()->y = vel.myY;

	}
}

bool GameObject::HasCollided(const v2& position)
{
	if ((GetPosition() - position).Length() < 5.f)
		return true;
	else
		return false;
}

int GameObject::EnableSprite(std::string_view sprName)
{
	// Disable all the sprite and enable the specified one
	for (SpriteMap::iterator itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
	{
		itSpr->second->m_Active = false;
	}
	m_Sprites.at(sprName.data())->m_Active = true;
	PlayAnimation(sprName.data());
	return retCode;
}

int GameObject::PlayAnimation(std::string_view sprName)
{
	if (m_Sprites.at(sprName.data())->GetAnim() != nullptr)
		m_Sprites.at(sprName.data())->GetAnim()->PlayAnimation();

	return retCode;
}

int GameObject::StopAnimations()
{
	// Disable all the sprite and enable the specified one
	for (SpriteMap::iterator itSpr = m_Sprites.begin(); itSpr != m_Sprites.end(); ++itSpr)
		if (itSpr->second->GetAnim() != nullptr)
			itSpr->second->GetAnim()->StopAnimation();

	return retCode;
}