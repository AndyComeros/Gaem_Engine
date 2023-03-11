#pragma once
#include "GameObject.h"
#include <vector>


//plz make singleton
class Scene
{
public:
	Scene();
	~Scene();

	CubeMap* skybox;
	std::vector<GameObject> gameObjects;
private:
	
};