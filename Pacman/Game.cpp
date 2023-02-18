#include "Game.h"
#include "Renderer.h"
#include "GameObject.h"
#include "Sprite.h"
#include "ResourceCache.h"




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

	/* Initialise the Resourses cache */
	m_Cache = new ResourceCache();
	m_Cache->AddTexture("Lv1Spritesheet", "PacmanSpritesheet.png", m_Renderer->GetSDLRenderer());

	/* Initialise Drawer and Pacman game */
	m_Drawer = new Drawer(m_Renderer->GetWindow(), m_Renderer->GetSDLRenderer());
	m_Pacman = Pacman::Create(m_Drawer);

	// add test game object
	std::string objName = "Packman";
	std::string sprName = "PackmanRight";
	AddGameObject(objName, new GameObject(new Sprite(sprName, m_Cache->GetTexture("Lv1Spritesheet")), true));

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

		//if (!m_Pacman->Update(elapsedTime))
		//	break;
		
		// Update the game objects
		for (auto itObj = m_GameObjects.begin(); itObj != m_GameObjects.end(); ++itObj)
		{
			itObj->second->Update();
		}

		SDL_SetRenderDrawColor(m_Renderer->GetSDLRenderer(), 0, 0, 0, 255);
		SDL_RenderClear(m_Renderer->GetSDLRenderer());

		//m_Pacman->Draw();

		lastFrame = currentFrame;

		// Render the game objects
		m_Renderer->Render(&m_GameObjects);

		SDL_RenderPresent(m_Renderer->GetSDLRenderer());
		
		if (k_FrameDelay > elapsedTime)
			SDL_Delay(k_FrameDelay - elapsedTime);	
	}

	return retCode;
}

int Game::Terminate()
{
	m_IsRunning = false;

	delete m_Pacman;
	delete m_Drawer;


	// Terminate the Renderer
	m_Renderer->Terminate();
	delete m_Renderer;

	return retCode;
}

int Game::AddGameObject(std::string_view objName, GameObject* gameObject)
{
	// insert the game object into the storage	
	m_GameObjects.emplace(objName, gameObject);
	return retCode;
}

int Game::RemoveGameObject(std::string_view objName)
{
	// Remove the game object
	GameObjectMap::iterator it;
	it = m_GameObjects.find(objName.data());
	m_GameObjects.erase(it);

	return retCode;
}

GameObject* Game::GetGameObject(std::string_view objName)
{
	// Retun the game object
	return m_GameObjects.at(objName.data());
}