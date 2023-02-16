#include "Sprite.h"
#include "TextureCache.h"


Sprite::Sprite(std::string& sprName, TextureCache* sprTex)
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

SDL_Texture* Sprite::GetTexture()
{
	return m_Texture->GetTexture();
}
