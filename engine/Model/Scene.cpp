#include "Scene.h"

Scene::Scene() {}

Scene::~Scene() {}

void Scene::AddObject(GameObject& gameObject) {
	gameObjects.insert(std::pair<std::string, GameObject*>(gameObject.name, &gameObject));
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

GameObject& Scene::GetObject(std::string objName) {
	return *gameObjects.at(objName);
}