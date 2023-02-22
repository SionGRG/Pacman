#pragma once
#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include <string>
#include <unordered_map>
#include "Vector2f.h"
#include "SDL.h"

#define retCode 0
#define errCode -1



typedef struct tagRECT
{
	long x, y, w, h;
} RECTL;

// Rectangle definer
struct RECTF
{
	float x, y, w, h;

	RECTF()
		:x(0), y(0), w(0), h(0)
	{};

	RECTF(float l, float t, float r, float b)
		:x(l), y(t), w(r), h(b)
	{};

	RECTF(const RECTF& r)
		:x(r.x), y(r.y), w(r.w), h(r.h)
	{};

	RECTF(const RECTL& r)
		:x((float)r.x), y((float)r.y), w((float)r.w), h((float)r.h)
	{};

	operator RECTL() {
		return RECTL{ (int)x, (int)y, (int)w, (int)h };
	}

	SDL_Rect GetSDLRect() {
		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;
		return rect;
	}
};

struct SDL_Texture;
typedef std::unordered_map<std::string, SDL_Texture*> TextureMap;

class Sprite;
typedef std::unordered_map<std::string, Sprite*> SpriteMap;

class GameObject;
typedef std::unordered_map<std::string, GameObject*> GameObjectMap;

typedef Vector2f v2;
// Json Data format loaded from TexturePacker packed files
struct SpriteData
{
	std::string			Name;
	RECTF				TexRect;	// Texture rectangle from a spritesheet, useful in animation
	v2					Size;
	v2					Pivot;
	bool				Gridded;	// When the rect is an animated rect sheet or just a packed rect sheet in a grid
	bool				Animated;	// is the sprite animated?
	bool				Loop;		// loop the animation
	float				Rate;		// Animation playback speed or switch rate
	v2					Grid;		// v2 (columns, rows)
};
typedef std::unordered_map<std::string, SpriteData> SpriteAtlasMap;


#endif // !__DATASTRUCTURES_H__