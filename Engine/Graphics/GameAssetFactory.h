#pragma once
#include "Asset.h"
#include <string>
#include <vector>
#include "readFile.h"
//#include "GameObject.h"

class GameAssetFactory
{
public:
	GameAssetFactory(const char* dir);

	//creates a new gameobject
	GameObject CreateGameObject (std::string id);

private:
	readFile readFile;
	Shader* defaultShader;

	std::vector<Asset> assets;
};

