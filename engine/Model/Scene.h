#pragma once
#include "GameObject.h"
#include "Terrain.h"
#include "Lighting.h"
#include <vector>

class Scene
{
public:
	Scene();

	~Scene();

	void AddObject(GameObject& gameObject);
	void SetSkybox(CubeMap* nSkybox);


	//all scene data
	Camera camera;
	CubeMap* skybox = nullptr;
	Lights lights;
	std::vector<GameObject> gameObjects;
private:
	

};