#pragma once
#include "Asset.h"
#include <string>
#include <vector>
#include "readFile.h"
#include "../GameObject.h"
#include "Model3D.h"
class GameAssetFactory
{
protected:
	static GameAssetFactory* gameAssetFactory_;

public:
	GameAssetFactory() {};
	
	static GameAssetFactory* GetInstance();

	void ReadInAssets(const char* dir);

	//creates a new gameobject
	GameObject CreateGameObject (std::string id);

	//deleting copy construtor
	GameAssetFactory(const GameAssetFactory& obj) = delete;

private:
	ReadFile readFile;
	
	std::vector<Asset> assets;
};

