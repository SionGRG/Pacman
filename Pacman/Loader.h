#pragma once
#ifndef __FILESLOADER__
#define __FILESLOADER__

#include "DataStructures.h"
#include "json/json.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

/*
	This class contains methods of Reading many kinds of files and loading many kinds of data
	* This include:
		- Loading SDL Textures
		- Reading JSON files
*/
class Loader
{
public:
	Loader();
	~Loader();

	int Init();
	int Terminate();

	/* Loading an SDL Texture */
	SDL_Texture* LoadSDLTexture(const std::string& texPath, SDL_Renderer* renderer);
	/* Reading data from a JSON file */
	Json::Value ReadJSONData(std::string& jsonFile);


private:


	bool m_Terminated = false;
};


#endif // !__FILESLOADER__