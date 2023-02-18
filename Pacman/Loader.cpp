#include "Loader.h"
#include <fstream>

Loader::Loader()
{
}

Loader::~Loader()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int Loader::Init()
{

	return retCode;
}

int Loader::Terminate()
{


	m_Terminated = true;
	return retCode;
}

SDL_Texture* Loader::LoadSDLTexture(const std::string& texPath, SDL_Renderer* renderer)
{
	SDL_Surface* texSurface = IMG_Load(texPath.c_str());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, texSurface);
	SDL_FreeSurface(texSurface);

	return texture;
}

Json::Value Loader::ReadJSONData(std::string& jsonFile)
{
	Json::Reader reader;
	Json::Value root;

	std::ifstream fJsonData(jsonFile);
	reader.parse(fJsonData, root, false);
	return root;
}
