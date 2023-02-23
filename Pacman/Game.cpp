#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Sprite.h"
#include "ResourceCache.h"
#include "PacmanLv1.h"


#define INITIAL_PACMAN


Game::Game()
{

}

Game::~Game()
{
	// Terminate the game when it goes out of scope
	if (Terminate() != retCode)
	{
		assert(0 && "Failed to terminate the Game");
		exit(errCode);
	}
}

int Game::Init()
{
	m_IsRunning = false;

	m_Renderer = new Renderer("Pacman");

#ifdef INITIAL_PACMAN

	/* Initialise Drawer and Pacman game */
	m_Drawer = new Drawer(m_Renderer->GetWindow(), m_Renderer->GetSDLRenderer());
	m_Pacman = Pacman::Create(m_Drawer);

#else	// NEW_PACMAN

	/* Initialise the level and Resourses cache */
	m_Cache = new ResourceCache();
	m_Cache->AddTexture("Lv1Spritesheet", "PacmanSpritesheet.png", m_Renderer->GetSDLRenderer());

	/* Load the Sprite atlas json data */
	m_Cache->LoadAtlasData("PacmanAtlasData.json");

	/* Add Pacman level 1 */
	m_Level01 = new PacmanLv1("Pacman Level 1", m_Cache);

#endif // INITIAL_PACMAN
	m_IsRunning = true;
	return retCode;
}

int Game::UpdateEvents()
{
	SDL_Event event;
	SDL_PollEvent(&event);

	switch (event.type)
	{
	case SDL_QUIT:
		m_IsRunning = false;
	default:
		break;
	}

	return retCode;
}

int Game::Update()
{
	float lastFrame = (float)SDL_GetTicks();

	while (m_IsRunning)
	{
		UpdateEvents();

		float currentFrame = (float)SDL_GetTicks();
		float elapsedTime = currentFrame - lastFrame;

#ifdef INITIAL_PACMAN

		if (!m_Pacman->Update(elapsedTime))
			break;

#else	// NEW_PACMAN

		m_Level01->Update(elapsedTime);

#endif // INITIAL_PACMAN

		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());

#ifdef INITIAL_PACMAN
		
		m_Pacman->Draw();
		
#else	// NEW_PACMAN
	
		// Render the game objects
		m_Renderer->Render(m_Level01->GetGameObjects());

#endif // INITIAL_PACMAN

		lastFrame = currentFrame;

		SDL_RenderPresent(m_Renderer->GetSDLRenderer());
		
		if (k_FrameDelay > elapsedTime)
			SDL_Delay(k_FrameDelay - elapsedTime);	
	}

	return retCode;
}

int Game::Terminate()
{
	m_IsRunning = false;

#ifdef INITIAL_PACMAN
	delete m_Pacman;
	delete m_Drawer;

#else	// NEW_PACMAN

	// Terminate the Renderer
	m_Renderer->Terminate();
	delete m_Renderer;

#endif // INITIAL_PACMAN

	return retCode;
}

