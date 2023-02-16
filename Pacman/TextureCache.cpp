#include "TextureCache.h"


TextureCache::TextureCache(const std::string& texName, const char* texPath, SDL_Renderer* renderer)
	: m_TexName(texName), m_TexPath(texPath)
{	
	Init(renderer);
}

TextureCache::~TextureCache()
{
	Terminate();
}

int TextureCache::Init(SDL_Renderer* renderer)
{
	SDL_Surface* texSurface = IMG_Load(m_TexPath);
	m_Texture = SDL_CreateTextureFromSurface(renderer, texSurface);
	SDL_FreeSurface(texSurface);

	return retCode;
}

int TextureCache::Terminate()
{
	if (!m_Terminated)
	{
		if (m_Texture != nullptr)
			delete m_Texture;

		m_Terminated = true;
	}

	return retCode;
}