#include "Texture.h"


Texture::Texture(const std::string& texName, const char* texPath, SDL_Renderer* renderer)
	: m_TexName(texName), m_TexPath(texPath)
{	
	Init(renderer);
}

Texture::~Texture()
{
	Terminate();
}

int Texture::Init(SDL_Renderer* renderer)
{
	SDL_Surface* texSurface = IMG_Load(m_TexPath);
	m_Texture = SDL_CreateTextureFromSurface(renderer, texSurface);
	SDL_FreeSurface(texSurface);

	return retCode;
}

int Texture::Terminate()
{
	if (m_Texture != nullptr)
		delete m_Texture;

	return retCode;
}