#pragma once
#include "GameObject.h"
#include "Terrain.h"
#include "Lighting.h"
#include <Physics.h>
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
	Physics physics;
	std::vector<GameObject> gameObjects;
private:
	

};