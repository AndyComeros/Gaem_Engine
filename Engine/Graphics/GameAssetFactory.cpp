#include "GameAssetFactory.h"

GameAssetFactory::GameAssetFactory(const char* dir)
{
	defaultShader = new Shader("Engine/Shaders/Default.frag", "Engine/Shaders/Default.frag", nullptr);

	readFile.loadAssetsFromFile(dir, assets);
}

GameObject GameAssetFactory::CreateGameObject(std::string id)
{
	GameObject object;
	for(Asset asset : assets)
	{
		if(asset.id.compare(id))
		{
			object.name = asset.name;
			object.mesh = asset.model;
			object.Transform = { 0.0, 0.0, 0.0 };
			object.Rotation = { 0.0, 0.0, 0.0 };
			object.Scale = { 1.0, 1.0, 1.0 };
			if (asset.Shader != nullptr)
				object.Shader = asset.Shader;
			else
				object.Shader = defaultShader;
			break;
		}
	}

	return object;
}