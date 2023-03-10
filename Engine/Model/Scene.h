#pragma once
#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();


	std::vector<GameObject> gameObjects;
private:
	
};