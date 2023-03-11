#pragma once
#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	CubeMap* skybox;
	std::vector<GameObject> gameObjects;
private:
	
};