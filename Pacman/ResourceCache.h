#pragma once
#ifndef __RESOURCECACHE_H__
#define __RESOURCECACHE_H__

#include <string>
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include "DataStructures.h"


class Loader;


/*
	A Resources Cache of the assets used in the Game
	* This inludes 
		- Textures
		- text Data like JSON Data
		- Sprite Data: information about the sprites
		- Audio Data
*/
class ResourceCache
{
public:
	ResourceCache();
	~ResourceCache();

	int Init();
	int Terminate();

	// Texture Functions
	int AddTexture(const std::string& texName,const std::string& texPath, SDL_Renderer* renderer);
	int RemoveTexture(std::string& texName);
	SDL_Texture* GetTexture(const std::string& texName);

private:

	Loader* m_Loader;
	
	TextureMap m_Textures;


	bool m_Terminated = false;
};


#endif // !__RESOURCECACHE_H__