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

	/* Load the Sprite atlas json data */
	m_Cache->LoadAtlasData("PacmanAtlasData.json");

	// add test game objects
	AddGameObject("Playfield", new GameObject(new Sprite(m_Cache->GetSpriteData("Playfield"), m_Cache->GetTexture("Lv1Spritesheet"), 0, 0), true));
	AddGameObject("PackmanOLeft", new GameObject(new Sprite(m_Cache->GetSpriteData("Pacman_Open_left_32"), m_Cache->GetTexture("Lv1Spritesheet"), 200, 200), true));
	AddGameObject("PackmanCRight", new GameObject(new Sprite(m_Cache->GetSpriteData("Pacman_Closed_right_32"), m_Cache->GetTexture("Lv1Spritesheet"), 100, 150), true));
	AddGameObject("RedGhost", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost1", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 120, 150), true));
	AddGameObject("RedGhost2", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 250, 150), true));
	AddGameObject("RedGhost3", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 150), true));
	AddGameObject("RedGhost4", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 360, 150), true));
	AddGameObject("RedGhost5", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 450), true));
	AddGameObject("RedGhost6", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 650), true));
	AddGameObject("RedGhost7", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 150, 150), true));
	AddGameObject("RedGhost8", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 170, 350), true));
	AddGameObject("RedGhost9", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 180, 250), true));
	AddGameObject("RedGhost10", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 200, 550), true));
	AddGameObject("RedGhost11", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 500, 350), true));
	AddGameObject("RedGhost12", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 350), true));
	AddGameObject("RedGhost13", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 350, 200), true));
	AddGameObject("RedGhost14", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 450, 100), true));
	AddGameObject("RedGhost15", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 320, 350), true));
	AddGameObject("RedGhost16", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 400, 250), true));
	AddGameObject("RedGhost17", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 460, 200), true));
	AddGameObject("RedGhost18", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 310, 170), true));
	AddGameObject("RedGhost19", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 030, 240), true));
	AddGameObject("RedGhost20", new GameObject(new Sprite(m_Cache->GetSpriteData("ghost_red_32"), m_Cache->GetTexture("Lv1Spritesheet"), 250, 300), true));

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