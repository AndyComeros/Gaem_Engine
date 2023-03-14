#pragma once
#include "GameObject.h"
#include "Lighting.h"
#include <vector>

class Scene
{
public:
	Scene();

	~Scene();

	//all scene data
	Camera camera;
	CubeMap* skybox = nullptr;
	Lights lights;
	std::vector<GameObject> gameObjects;


private:

};