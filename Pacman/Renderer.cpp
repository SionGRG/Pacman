#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"
#include <assert.h>
#include <algorithm>
#include "GameObject.h"
#include "Sprite.h"
#include "Text.h"

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
					SDL_RenderCopy(m_Renderer, itSpr->second->GetTexture(), &itSpr->second->GetTextureRect()->GetSDLRect(), &itSpr->second->GetPosRect()->GetSDLRect());
				}
			}
		}
	}

	// Render the texts 
	std::for_each(m_Texts.begin(), m_Texts.end(), [](Text* text) { text->Render(); });

	return retCode;
}

int Renderer::Terminate()
{
	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);

	// Deallocate the texts memory
	std::for_each(m_Texts.begin(), m_Texts.end(), [](Text* text) { delete text; });
	m_Texts.clear();

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	m_Terminated = true;
	return retCode;
}

void Renderer::RenderStaticText(std::string_view textData, std::string_view fontFile, int xPos, int yPos, int fontSize, COLOUR rgbaColour)
{
	Text* text = new Text(m_Renderer, textData, fontFile, xPos, yPos, fontSize, rgbaColour);

	m_Texts.emplace_back(text);
}

void Renderer::RenderText(std::string_view textData, std::string_view fontFile, int xPos, int yPos, int fontSize, COLOUR rgbaColour)
{
	TTF_Font* font = TTF_OpenFont(fontFile.data(), fontSize);

	SDL_Surface* surface = TTF_RenderText_Solid(font, textData.data(), rgbaColour);

	if (!surface)
		return;

	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_Renderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;

	posRect.x = xPos;
	posRect.y = yPos;
	SDL_QueryTexture(texture, nullptr, nullptr, &posRect.w, &posRect.h);

	SDL_RenderCopy(m_Renderer, texture, &sizeRect, &posRect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}
