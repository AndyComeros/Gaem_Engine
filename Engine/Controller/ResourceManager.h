#pragma once

#include <map>
#include <Graphics.h>
#include <Model.h>



class ResourceManager
{
public:
	
	ResourceManager& Get();

	void LoadTexture(std::string fileName, std::string resName);
	void LoadModel(std::string fileName, std::string resName);
	void LoadShader(std::string vertPath, std::string fragPath, std::string geomPath, std::string resName);

	Texture* GetTexture(std::string resName);
	Model* GetModel(std::string resName);
	Shader* GetShader(std::string resName);

private:

	ResourceManager();
	~ResourceManager();

	std::map<std::string,Texture> textures;
	std::map<std::string, Model> models;
	std::map<std::string, Shader> shaders;
};

