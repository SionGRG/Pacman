#pragma once
#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include <string>
#include <unordered_map>

#define retCode 0
#define errCode -1


struct SDL_Texture;
typedef std::unordered_map<std::string, SDL_Texture*> TextureMap;

class Sprite;
typedef std::unordered_map<std::string, Sprite*> SpriteMap;

class GameObject;
typedef std::unordered_map<std::string, GameObject*> GameObjectMap;


#endif // !__DATASTRUCTURES_H__