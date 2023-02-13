#include "Game.h"


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

	/* initialize SDL */
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		assert(0 && "Failed to initialize video!");
		return errCode;
	}

	/* Initialise window and renderer */
	m_Window = SDL_CreateWindow("Pacman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768, SDL_WINDOW_OPENGL);
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

	/* Initialise Drawer and Pacman game */
	m_Drawer = new Drawer(m_Window, m_Renderer);
	m_Pacman = Pacman::Create(m_Drawer);

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
	float lastFrame = (float)SDL_GetTicks() * 0.001f;

	while (m_IsRunning)
	{
		UpdateEvents();

		float currentFrame = (float)SDL_GetTicks() * 0.001f;
		float elapsedTime = currentFrame - lastFrame;

		if (!m_Pacman->Update(elapsedTime))
			break;

		SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer);

		m_Pacman->Draw();

		lastFrame = currentFrame;

		SDL_RenderPresent(m_Renderer);
		SDL_Delay(1);
	}

	return retCode;
}

int Game::Terminate()
{
	m_IsRunning = false;

	delete m_Pacman;
	delete m_Drawer;

	SDL_DestroyWindow(m_Window);
	SDL_DestroyRenderer(m_Renderer);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return retCode;
}