#include "Sprite.h"
#include "ResourceCache.h"
#include "SDL.h"

Sprite::Sprite(std::string& sprName, SDL_Texture* sprTex)
	:m_Name(sprName), m_Texture(sprTex)
{
	Init();
}

Sprite::~Sprite()
{
	Terminate();
}

int Sprite::Init()
{

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
