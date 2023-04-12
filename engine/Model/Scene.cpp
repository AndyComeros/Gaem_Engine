#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddObject(GameObject& go) {
	gameObjects.push_back(go);
}