#include "GameAssetFactory.h"

GameAssetFactory* GameAssetFactory::gameAssetFactory_;

GameAssetFactory* GameAssetFactory::GetInstance()
{
	if (gameAssetFactory_ == NULL)
	{
		gameAssetFactory_ = new GameAssetFactory();

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
		if (asset.id.compare(id) == 0)
		{
			object.name = asset.name;
			std::cout << asset.name;
			object.model_data = asset.model;
			if (asset.Diffuse != nullptr)
				object.model_data->SetDiffuseTexture(asset.Diffuse);
			if (asset.Emission != nullptr)
				object.model_data->SetEmissionTexture(asset.Emission);
			object.position = { 0.0, 0.0, 0.0 };
			object.rotation = { 0.0, 0.0, 0.0 };
			object.scale = { 1.0, 1.0, 1.0 };
			if (asset.Shader != nullptr)
				object.shader = asset.Shader;
			break;
		}
	}

	return object;
}