#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddObject(GameObject& gameObject) {
	gameObjects.push_back(gameObject);
}

void Scene::SetSkybox(CubeMap* nSkybox) {
	skybox = nSkybox;
}