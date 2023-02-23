#include "Sprite.h"
#include "ResourceCache.h"
#include "Animation.h"
#include "SDL.h"
#include "GameObject.h"

Sprite::Sprite(SpriteData* sprData, SDL_Texture* sprTex, v2& pos)
	:m_SprData(sprData), m_Texture(sprTex), m_Pos(pos)
{
	Init();
}

Sprite::~Sprite()
{
	Terminate();
}

int Sprite::Init()
{


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
	}

	return retCode;
}

int Sprite::Update(float& elapsedTime, GameObject* parent)
{
	if (m_Active)	// Only update active sprites
	{
		if (m_SprData != nullptr && m_SprData->Gridded)
			m_Animation->Update(elapsedTime);

	}

	return retCode;
}

int Sprite::Terminate()
{
	if (!m_Terminated)
	{
		m_Texture = nullptr;
		delete m_Texture;

		m_Terminated = true;
	}
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
