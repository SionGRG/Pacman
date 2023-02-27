#include "Text.h"


Text::Text(SDL_Renderer* renderer, std::string_view text, std::string_view fontFile, int xPos, int yPos, int FontSize, COLOUR rgbaColour)
	: m_Renderer(renderer), m_TextData(text), m_FontFile(fontFile.data()),m_FontSize(FontSize), m_Colour(rgbaColour)
{
	Init(xPos, yPos);
}

Text::~Text()
{
	if (!m_Terminated)
		Terminate();
}

int Text::Init(int& xPos, int& yPos)
{
	m_Font = TTF_OpenFont(m_FontFile, m_FontSize);

	m_Surface = TTF_RenderText_Solid(m_Font, m_TextData.c_str(), m_Colour);
	m_Texture = SDL_CreateTextureFromSurface(m_Renderer, m_Surface);
	SDL_FreeSurface(m_Surface);

	m_Position.x = xPos;
	m_Position.y = yPos;

	SDL_QueryTexture(m_Texture, nullptr, nullptr, &m_Position.w, &m_Position.h);

	return retCode;
}

int Text::Render()
{
	SDL_RenderCopy(m_Renderer, m_Texture, nullptr, &m_Position);
	return retCode;
}

int Text::Terminate()
{
	SDL_DestroyTexture(m_Texture);
	TTF_CloseFont(m_Font);

	return retCode;
}
