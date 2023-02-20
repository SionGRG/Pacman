#include "Sprite.h"
#include "ResourceCache.h"
#include "SDL.h"

Sprite::Sprite(SpriteData* sprData, SDL_Texture* sprTex, int xPos, int yPos)
	:m_SprData(sprData), m_Texture(sprTex)
{
	Init(xPos, yPos);
}

Sprite::~Sprite()
{
	Terminate();
}

int Sprite::Init(int& xPos, int& yPos)
{
	/* initialise the position rect */
	m_PosRect.x = xPos;
	m_PosRect.y = yPos;
	m_PosRect.w = m_SprData->Size.myX;
	m_PosRect.h = m_SprData->Size.myY;


	return retCode;
}

int Sprite::Update()
{
	if (m_Active)	// Only update active sprites
	{

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
