#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddObject(GameObject& gameObject) {
	gameObjects.push_back(gameObject);
}

void Scene::AddLights(Lights& nLights) {
	lights = nLights;
}

void Scene::SetSkybox(CubeMap* nSkybox) {
	skybox = nSkybox;
}

Camera& Scene::GetCamera() {
	return camera;
}

Lights& Scene::GetLights() {
	return lights;
}