#include "ResourceCache.h"
#include "Loader.h"



ResourceCache::ResourceCache()
{
	Init();
}

ResourceCache::~ResourceCache()
{
	if (!m_Terminated)
	{
		Terminate();
	}
}

int ResourceCache::Init()
{
	m_Loader = new Loader();


	return retCode;
}

int ResourceCache::Terminate()
{
	if (m_Loader != nullptr)
		delete m_Loader;

	// Clear texture memory
	for (TextureMap::iterator itTex = m_Textures.begin(); itTex != m_Textures.end(); ++itTex)
		free(itTex->second);

	m_Textures.clear();

	m_Terminated = true;

	return retCode;
}

int ResourceCache::AddTexture(std::string_view texName, std::string_view texPath, SDL_Renderer* renderer)
{
	// Load the texture using the File Loader
	SDL_Texture* tex = m_Loader->LoadSDLTexture(texPath, renderer);

	// Add the texture to the texture container
	m_Textures.emplace(texName, tex);

	return retCode;
}

int ResourceCache::RemoveTexture(std::string_view texName)
{
	// Remove the texture from the texture container
	TextureMap::iterator it;
	it = m_Textures.find(texName.data());
	free(it->second);	// clear texture memory
	m_Textures.erase(it);

	return retCode;
}

SDL_Texture* ResourceCache::GetTexture(const std::string_view texName)
{
	return m_Textures.at(texName.data());
}

int ResourceCache::LoadAtlasData(std::string_view atlasJsonData)
{
	// Load the json sprite atlas data
	Json::Value root = m_Loader->ReadJSONData(atlasJsonData);

	SpriteData sprData;

	for (int i = 0; i < root["frames"].size(); ++i)
	{
		sprData.Name = root["frames"][i]["filename"].asCString(),

		sprData.TexRect = RECTF{
			root["frames"][i]["frame"]["x"].asFloat(),
			root["frames"][i]["frame"]["y"].asFloat(),
			root["frames"][i]["frame"]["w"].asFloat(),
			root["frames"][i]["frame"]["h"].asFloat()
		},
		sprData.Size = v2(
			root["frames"][i]["frame"]["w"].asFloat() / root["frames"][i]["grid"]["columns"].asInt(),
			root["frames"][i]["frame"]["h"].asFloat() / root["frames"][i]["grid"]["rows"].asInt()
		),

		sprData.Gridded = root["frames"][i]["gridded"].asBool(),

		sprData.Animated = root["frames"][i]["animated"].asBool(),

		sprData.Loop = root["frames"][i]["loop"].asBool(),

		sprData.Rate = root["frames"][i]["rate"].asFloat(),

		sprData.Grid = v2(
			root["frames"][i]["grid"]["columns"].asInt(),
			root["frames"][i]["grid"]["rows"].asInt()
		);

		// Add sprite to the atlas data
		m_SpriteAtlasData.emplace(sprData.Name, sprData);
	}

	return retCode;
}

SpriteData* ResourceCache::GetSpriteData(std::string_view spriteName)
{
	return &m_SpriteAtlasData.at(spriteName.data());
}
