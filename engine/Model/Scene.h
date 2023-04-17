#pragma once
#include "GameObject.h"
#include "Terrain.h"
#include "Lighting.h"
#include <Physics.h>
#include <map>

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
	GameObject& GetObject(std::string objName);

	//all scene data
	Camera camera;
	CubeMap* skybox = nullptr;
	Lights lights;
	Physics physics;
	std::map<std::string,GameObject> gameObjects;
private:
	

};