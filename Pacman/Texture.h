#pragma once
#ifndef __TEXTURE__
#define __TEXTURE__

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

#define retCode 0
#define errCode -1

/*
	An abstraction of the creating an SDL Texture
*/

class Texture
{
public:
	Texture(const std::string& texName, const char* texPath, SDL_Renderer* renderer);
	~Texture();

	int Init(SDL_Renderer* renderer);
	int Terminate();

	const std::string GetName() { return m_TexName; }
	SDL_Texture* GetTexture() { return m_Texture; }

private:
	std::string m_TexName;
	const char* m_TexPath;
	SDL_Texture* m_Texture;
};


#endif // !__TEXTURE__