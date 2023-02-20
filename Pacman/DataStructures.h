#pragma once
#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include <string>
#include <unordered_map>
#include "Vector2f.h"
#include "SDL.h"

#define retCode 0
#define errCode -1


struct SDL_Texture;
typedef std::unordered_map<std::string, SDL_Texture*> TextureMap;

class Sprite;
typedef std::unordered_map<std::string, Sprite*> SpriteMap;

class GameObject;
typedef std::unordered_map<std::string, GameObject*> GameObjectMap;

typedef Vector2f v2;
typedef SDL_Rect RECT;
// Json Data format loaded from TexturePacker packed files
struct SpriteData
{
	std::string			Name;
	SDL_Rect			TexRect;	// Texture rectangle from a spritesheet, useful in animation
	v2					Size;
	v2					Pivot;
};

typedef std::unordered_map<std::string, SpriteData> SpriteAtlasMap;

#endif // !__DATASTRUCTURES_H__