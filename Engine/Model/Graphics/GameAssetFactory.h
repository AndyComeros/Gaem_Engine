#pragma once
#include "Asset.h"
#include <string>
#include <vector>
#include "readFile.h"
#include "../GameObject.h"

//singleton class so it can be accessed rom anywhere bu calling getInstance
//just need to run readInAssets, once for it to be usable
class GameAssetFactory
{
protected:
	static GameAssetFactory* gameAssetFactory_;

public:
	GameAssetFactory() {};
	static GameAssetFactory* getInstance();

	void ReadInAssets(const char* dir);

	//creates a new gameobject
	GameObject CreateGameObject (std::string id);


	//deleting copy construtor
	GameAssetFactory(const GameAssetFactory& obj) = delete;

private:
	readFile readFile;
	
	std::vector<Asset> assets;
};

