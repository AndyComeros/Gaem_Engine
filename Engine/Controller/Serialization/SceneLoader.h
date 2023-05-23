#pragma once
#include <Scene.h>
#include <NPC.h>
#include <Terrain.h>
#include <json/json.h>
#include <fstream>


class SceneLoader
{
public:
	SceneLoader();
	~SceneLoader();

	//save a scene into json format.
	void SaveScene(Scene* scene, const std::string outName);

	//load a scene from json file.
	Scene* LoadScene(const std::string inName);


	void* SaveObject();
private:

	

};
