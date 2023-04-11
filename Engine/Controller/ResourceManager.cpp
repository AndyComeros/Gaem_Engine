#include "ResourceManager.h"


ResourceManager& ResourceManager::Get() {
	
	static ResourceManager r_instance;
	return r_instance;
}

ResourceManager::ResourceManager(){

	//load defaults
}

ResourceManager::~ResourceManager(){}

void ResourceManager::LoadTexture(std::string fileName, std::string resName) {
	try
	{
		textures.emplace(resName, Texture(fileName.c_str()));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not load: " << resName << std::endl;
	}
}

void ResourceManager::LoadModel(std::string fileName, std::string resName) {
	try
	{
		models.emplace(resName, Model(fileName.c_str()));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not load: " << resName << std::endl;
	}
}

void ResourceManager::LoadShader(std::string vertPath, std::string fragPath, std::string geomPath, std::string resName) {
	try
	{
		shaders.emplace(resName, Shader(vertPath.c_str(), fragPath.c_str(), geomPath.c_str()));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not load: " << resName << std::endl;
	}
}

Texture* ResourceManager::GetTexture(std::string resName) {
	Texture* texture;
	try
	{
		texture = &textures.at(resName);
	}
	catch (const std::exception&)
	{
		std::cout << "Texture: '" << resName << "' does not exist" << std::endl;
		texture = nullptr;
	}
	return texture;
}

Model* ResourceManager::GetModel(std::string resName) {
	Model* model;
	try
	{
		model = &models.at(resName);
	}
	catch (const std::exception&)
	{
		std::cout << "Model: '" << resName << "' does not exist" << std::endl;
		model = nullptr;
	}
	return model;
}

Shader* ResourceManager::GetShader(std::string resName) {
	Shader* shader;
	try
	{
		shader = &shaders.at(resName);
	}
	catch (const std::exception&)
	{
		std::cout << "Shader: '" << resName << "' does not exist" << std::endl;
		shader = nullptr;
	}
	return shader;
}