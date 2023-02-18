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

SDL_Texture* Loader::LoadSDLTexture(std::string_view texPath, SDL_Renderer* renderer)
{
	SDL_Surface* texSurface = IMG_Load(texPath.data());
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, texSurface);
	SDL_FreeSurface(texSurface);

	return texture;
}

Json::Value Loader::ReadJSONData(std::string_view jsonFile)
{
	Json::Reader reader;
	Json::Value root;

	std::ifstream fJsonData(jsonFile.data());
	reader.parse(fJsonData, root, false);
	return root;
}
