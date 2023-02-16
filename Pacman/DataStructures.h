#pragma once
#ifndef __DATASTRUCTURES_H__
#define __DATASTRUCTURES_H__

#include <string>
#include <unordered_map>

#define retCode 0
#define errCode -1

class Sprite;
class GameObject;


typedef std::unordered_map<std::string, Sprite*> SpriteMap;
typedef std::unordered_map<std::string, GameObject*> GameObjectMap;


#endif // !__DATASTRUCTURES_H__