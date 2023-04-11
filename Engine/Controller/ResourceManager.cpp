#include "ResourceManager.h"


ResourceManager& ResourceManager::Get() {
	
	static ResourceManager r_instance;
	return r_instance;
}

ResourceManager::ResourceManager(){}
ResourceManager::~ResourceManager(){}

void ResourceManager::LoadTexture(std::string fileName, std::string resName) {
	textures.emplace(resName,Texture(fileName.c_str()));
}

void ResourceManager::LoadModel(std::string fileName, std::string resName) {
	models.emplace(resName, Model(fileName.c_str()));
}

void ResourceManager::LoadShader(std::string vertPath, std::string fragPath, std::string geomPath, std::string resName) {
	shaders.emplace(resName, Shader(vertPath.c_str(),fragPath.c_str(),geomPath.c_str()));
}

Texture* ResourceManager::GetTexture(std::string resName) {
	return &textures.at(resName);
}
Model* ResourceManager::GetModel(std::string resName) {
	return &models.at(resName);
}
Shader* ResourceManager::GetShader(std::string resName) {
	return &shaders.at(resName);
}