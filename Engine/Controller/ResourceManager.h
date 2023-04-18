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
	void LoadCubemap(std::string resName, std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back);

	//right, left, top, bottom, front, back.
	Texture* GetTexture(std::string resName);
	Model* GetModel(std::string resName);
	Shader* GetShader(std::string resName);
	CubeMap* GetCubeMap(std::string resName);


	auto TextureBegin() { return textures.begin(); }
	auto TextureEnd() { return textures.end(); }
						
	auto ModelBegin() { return models.begin(); }
	auto ModelEnd() { return models.end(); }
						
	auto ShaderBegin() { return shaders.begin(); }
	auto ShaderEnd() { return shaders.end(); }
						
	auto CubeMapBegin() { return cubemaps.begin(); }
	auto CubeMapEnd() { return cubemaps.end(); }
private:

	unsigned int IDIndex = 1;

	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;

	std::map<std::string, Texture*> textures;
	std::map<std::string, Model*> models;
	std::map<std::string, Shader*> shaders;
	std::map<std::string, CubeMap*> cubemaps;
};

