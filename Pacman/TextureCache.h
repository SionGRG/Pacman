#pragma once
#ifndef __TEXTURECACHE_H__
#define __TEXTURECACHE_H__

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "DataStructures.h"

/*
	An abstraction of the creating an SDL Texture
*/

class TextureCache
{
public:
	TextureCache(const std::string& texName, const char* texPath, SDL_Renderer* renderer);
	~TextureCache();

	int Init(SDL_Renderer* renderer);
	int Terminate();

	const std::string GetName() { return m_TexName; }
	SDL_Texture* GetTexture() { return m_Texture; }

private:
	std::string m_TexName;
	const char* m_TexPath;
	SDL_Texture* m_Texture;
	bool m_Terminated = false;
};


#endif // !__TEXTURECACHE_H__