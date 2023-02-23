#include "Renderer.h"
#include "SDL_ttf.h"
#include "SDL_image.h"
#include <assert.h>
#include "GameObject.h"
#include "Sprite.h"

Renderer::Renderer(const char* gameName)
{
	Init(gameName);
}

Renderer::~Renderer()
{
	if (!m_Terminated)
	{
		// Terminate the renderer when it goes out of scope
		if (Terminate() != retCode)
		{
			assert(0 && "Failed to terminate the Renderer");
			exit(errCode);
		}
	}
}

int Renderer::Init(const char* gameName)
{
	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		assert(0 && "Failed to initialize video!");
		return errCode;
	}

	/* Initialise window and renderer */
	m_Window = SDL_CreateWindow(gameName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED);

	if (!m_Window)
	{
		assert(0 && "Failed to create window!");
		return errCode;
	}

	/* initialize SDL_IMG and SDL_TTF */
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

	if (TTF_Init() == -1)
	{
		assert(0 && "Failed to create ttf!");
		exit(-1);
	}

	return retCode;
}

//int Renderer::Render(std::vector<GameObject*>& gameObjects);
int Renderer::Render(GameObjectMap* gameObjects)
{

	// Render the games objects
	//for (auto currentGameObject : gameObjects)
	for (auto itObj = gameObjects->begin(); itObj != gameObjects->end(); ++itObj)
	{
		//if (currentGameObject->second->m_Active) // only render active game objects
		if (itObj->second->m_Active) // only render active game objects
		{
			//auto c_Sprites = currentGameObject->GetSprites();
			auto c_Sprites = itObj->second->GetSprites();

			for (auto itSpr = c_Sprites->begin(); itSpr != c_Sprites->end(); ++itSpr)
			{
				if (itSpr->second->m_Active) // only render active sprites
				{
					SDL_RenderCopy(m_Renderer, itSpr->second->GetTexture(), &itSpr->second->GetTextureRect()->GetSDLRect(), &itObj->second->GetPosRect()->GetSDLRect());
				}
			}
		}
	}


	return retCode;
}

int Renderer::Terminate()
{
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	m_Terminated = true;
	return retCode;
}

