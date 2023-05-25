#pragma once
#include <ResourceManager.h>
#include <AI/AIManager.h>
#include <Physics/Physics.h>
#include <Scene.h>
#include <NPC.h>
#include <Terrain.h>
#include <json/json.h>
#include <fstream>
#include <filesystem>
#include <sys/stat.h>

class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader();

	//save a scene into json format.
	void SaveScene(Scene* scene, const std::string outName);

	//load a scene from json file.
	Scene& LoadScene(const std::string inName);

	
	std::vector<std::string> GetSaves(const std::string path);
	


private:
	Json::Value ObjectToJson(GameObject* obj);

	Json::Value LightsToJson(Lights* lights);

};
