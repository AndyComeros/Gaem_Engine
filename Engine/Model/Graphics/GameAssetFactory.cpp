#include "GameAssetFactory.h"

GameAssetFactory* GameAssetFactory::gameAssetFactory_;

GameAssetFactory* GameAssetFactory::getInstance()
{
	if (gameAssetFactory_ == NULL)
	{
		gameAssetFactory_ =  new GameAssetFactory();

		return gameAssetFactory_;
	}
	else
	{

		return gameAssetFactory_;
	}
}

void GameAssetFactory::ReadInAssets(const char* dir)
{
	readFile.LoadAssetsFromFile(dir, assets);
}

GameObject GameAssetFactory::CreateGameObject(std::string id)
{
	GameObject object;
	for (Asset asset : assets)
	{
		if (asset.id.compare(id))
		{
			object.name = asset.name;
			object.model_data = asset.model;
			object.position = { 0.0, 0.0, 0.0 };
			object.rotation = { 0.0, 0.0, 0.0 };
			object.scale = { 1.0, 1.0, 1.0 };
			if (asset.Shader != nullptr)
				object.shader = asset.Shader;
			else
				object.shader = nullptr;
			break;
		}
	}

	return object;
}
