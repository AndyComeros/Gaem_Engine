#pragma once

#include <map>
#include <Gameobject.h>
#include <vector>//temp

class ResourceManager
{
public:
	
	static ResourceManager& Get();

	GameObject CreateGameObject(std::string modelName, std::string shaderName);

	void LoadTexture(std::string resName, std::string fileName);
	void LoadModel	(std::string resName, std::string fileName, std::string difTexPath, std::string emisTexPath, std::string specTexPath);
	void LoadShader	(std::string resName, std::string vertPath, std::string fragPath, std::string geomPath);

	Texture* GetTexture(std::string resName);
	Model* GetModel(std::string resName);
	Shader* GetShader(std::string resName);

	void PrintTest(std::string printME) { std::cout << printME << std::endl; }

private:

	unsigned int IDIndex = 1;

	ResourceManager();
	~ResourceManager();
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator = (const ResourceManager&) = delete;

	std::map<std::string, Texture> textures;
	std::map<std::string, Model> models;
	std::map<std::string, Shader> shaders;

	//links texture names and texture file paths
	std::map<std::string, std::string> textureNames;
};

