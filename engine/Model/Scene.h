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

	void AddObject(GameObject& gameObject);
	void AddLights(Lights& nLights);
	void SetSkybox(CubeMap* nSkybox);
	Camera& GetCamera();
	Lights& GetLights();

	//all scene data
	Camera camera;
	CubeMap* skybox = nullptr;
	Lights lights;
	Physics physics;
	std::vector<GameObject> gameObjects;
private:
	

};