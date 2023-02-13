#ifndef DRAWER_H
#define DRAWER_H

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Surface;

class Drawer
{
public:

	Drawer(SDL_Window* aWindow, SDL_Renderer* aRenderer);
	~Drawer(void);

	void Draw(const char* anImage, int aCellX = 0, int aCellY = 0);
	void DrawText(const char* aText, const char* aFontFile, int aX, int aY);

private:
	bool Init();
	
	SDL_Window*		m_Window;
	SDL_Renderer*	m_Renderer;
	SDL_Surface*	m_World;
};

#endif // DRAWER_H