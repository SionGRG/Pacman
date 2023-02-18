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

int ResourceCache::AddTexture(const std::string& texName, const std::string& texPath, SDL_Renderer* renderer)
{
	// Load the texture using the File Loader
	SDL_Texture* tex = m_Loader->LoadSDLTexture(texPath, renderer);

	// Add the texture to the texture container
	m_Textures.emplace(texName, tex);

	return retCode;
}

int ResourceCache::RemoveTexture(std::string& texName)
{
	// Remove the texture from the texture container
	TextureMap::iterator it;
	it = m_Textures.find(texName);
	free(it->second);	// clear texture memory
	m_Textures.erase(it);

	return retCode;
}

SDL_Texture* ResourceCache::GetTexture(const std::string& texName)
{
	return m_Textures.at(texName);
}
