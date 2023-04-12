#pragma once

#include <map>
#include <Gameobject.h>
#include <Terrain.h>

class ResourceManager
{
public:
	
	static ResourceManager& Get();

	GameObject CreateGameObject(std::string objectName, std::string modelName, std::string shaderName);
	Terrain CreateTerrain(std::string terrainName, std::string heightMapName, std::vector<std::string> layerTextures, std::string detailName, float scaleX, float scaleY, float scaleZ);

	void LoadTexture(std::string resName, std::string fileName);
	void LoadModel	(std::string resName, std::string fileName, std::string diffName, std::string emisName, std::string specName);
	void LoadShader	(std::string resName, std::string vertPath, std::string fragPath, std::string geomPath);

	Texture* GetTexture(std::string resName);
	Model* GetModel(std::string resName);
	Shader* GetShader(std::string resName);

private:

	unsigned int IDIndex = 1;

	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;

	std::map<std::string, Texture*> textures;
	std::map<std::string, Model*> models;
	std::map<std::string, Shader*> shaders;
};

