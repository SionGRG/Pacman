#include "Sprite.h"
#include "ResourceCache.h"
#include "Animation.h"
#include "SDL.h"
#include "GameObject.h"
#include "Collider.h"

Sprite::Sprite(SpriteData* sprData, SDL_Texture* sprTex, v2& pos, bool EnableCollision)
	: m_SprData(sprData), m_Texture(sprTex), m_Pos(pos), m_CollisionStatus(EnableCollision)
{
	Init();
}

Sprite::~Sprite()
{
	if (!m_Terminated)
		Terminate();
}

int Sprite::Init()
{
	// Set the scale of the sprite
	m_Scale = v2(1,1);

	/* Define the texture rectangle of the sprite */
	if (m_SprData != nullptr)
	{
		if (m_SprData->Gridded)
		{
			m_Animation = new Animation(this, m_SprData->Rate, m_SprData->Loop);
		}
		else
		{
			DefineTextureRect(&m_SprData->TexRect);
		}
		/* initialise the position rect */
		m_PosRect = RECTF(m_Pos.myX, m_Pos.myY, m_SprData->Size.myX * m_Scale.myX, m_SprData->Size.myY * m_Scale.myY);

		// Initialise the collision box
		if (m_CollisionStatus)
			m_CollisionBox = new Collider2D(m_SprData->Name, m_CollisionStatus, v2(m_PosRect.w, m_PosRect.h), v2(m_PosRect.x, m_PosRect.y), v2(0, 0));
	}

	return retCode;
}

int Sprite::Update(float& elapsedTime, GameObject* parent)
{
	if (m_Active)	// Only update active sprites
	{
		if (m_SprData != nullptr && m_SprData->Gridded)
			m_Animation->Update(elapsedTime);

		// Update the collision box
		if (m_CollisionStatus)
			m_CollisionBox->Update(parent, this);
		
	}

	return retCode;
}

int Sprite::Terminate()
{
	m_Texture = nullptr;
	delete m_Texture;

	m_SprData = nullptr;
	delete m_SprData;

	m_Animation = nullptr;
	delete m_Animation;
	
	m_CollisionBox = nullptr;
	delete m_CollisionBox;

	m_Terminated = true;
	
	return retCode;
}

int Sprite::DefineTextureRect(RECTF* texDim)
{
	if (texDim == nullptr)
		return retCode;
	
	m_TexRect = *texDim;

	return retCode;
}

int Sprite::DefineTextureRect(int& frameIndex)
{
	auto frames = m_Animation->GetAnimationFrames();

	if (frameIndex >= frames->size())
	{
		frameIndex = frames->size();
		return retCode;
	}
	if (frameIndex < 0)
	{
		frameIndex = frames->size();
		return retCode;
	}
	DefineTextureRect(&frames->at(frameIndex));

	return retCode;
}


RECTB* Sprite::GetCollisionBox()
{
	return m_CollisionBox->GetCollisionBox();
}