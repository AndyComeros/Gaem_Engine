#pragma once
#include "GameObject.h"
#include <vector>

class Scene
{
public:
	Scene();
	~Scene();

	Camera camera;	
	CubeMap skybox;
	std::vector<GameObject> gameObjects;
private:
	
};