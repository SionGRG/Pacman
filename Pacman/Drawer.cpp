#include "Drawer.h"
#include "SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"

Drawer::Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer)
: m_Window(aWindow)
, m_Renderer(aRenderer)
{
}

Drawer::~Drawer(void)
{
	delete m_Window;
	delete m_Renderer;
	delete m_World;
}

bool Drawer::Init()
{
	if (!m_Window)
		return false;

	return true;
}

void Drawer::Draw(const char* anImage, int aCellX, int aCellY)
{
	SDL_Surface* surface = IMG_Load( anImage ) ;

	if (!surface)
		return;

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(m_Renderer, surface);
	SDL_FreeSurface(surface);

    SDL_Rect sizeRect;
    sizeRect.x = 0 ;
    sizeRect.y = 0 ;
    sizeRect.w = surface->w ;
    sizeRect.h = surface->h ;

    SDL_Rect posRect ;
    posRect.x = aCellX;
    posRect.y = aCellY;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(m_Renderer, optimizedSurface, &sizeRect, &posRect);
}

void Drawer::DrawText(const char* aText, const char* aFontFile, int aX, int aY)
{
		TTF_Font* font=TTF_OpenFont(aFontFile, 24);

		SDL_Color fg={255,0,0,255};
		SDL_Surface* surface = TTF_RenderText_Solid(font, aText, fg);

		SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(m_Renderer, surface);

		SDL_Rect sizeRect;
		sizeRect.x = 0 ;
		sizeRect.y = 0 ;
		sizeRect.w = surface->w ;
		sizeRect.h = surface->h ;

		SDL_Rect posRect ;
		posRect.x = aX;
		posRect.y = aY;
		posRect.w = sizeRect.w;
		posRect.h = sizeRect.h;

		SDL_RenderCopy(m_Renderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}
