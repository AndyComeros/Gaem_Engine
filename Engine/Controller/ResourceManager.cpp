#include "ResourceManager.h"


ResourceManager& ResourceManager::Get() {
	
	static ResourceManager r_instance;
	return r_instance;
}

ResourceManager::ResourceManager(){

	//load defaults
}

ResourceManager::~ResourceManager(){}


GameObject ResourceManager::CreateGameObject(std::string objectName, std::string modelName, std::string shaderName) {
	GameObject gameObject;
	gameObject.name = objectName;
	gameObject.SetID(IDIndex);
	IDIndex++;

	gameObject.model_data = GetModel(modelName);
	gameObject.shader = GetShader(shaderName);

	return gameObject;
}

void ResourceManager::LoadTexture(std::string resName, std::string fileName) {
	try
	{
		textures.emplace(resName, Texture(fileName.c_str()));
		textureNames.emplace(fileName, resName);
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not create: " << resName << std::endl;
	}
}

void ResourceManager::LoadModel(std::string resName, std::string fileName, std::string diffName, std::string emisName, std::string specName) {
	try
	{
		//model
		models.emplace(resName, Model(fileName.c_str()));

		//textures
		if (diffName != "" && textures.find(diffName) != textures.end())
			models.at(resName).SetDiffuseTexture(&textures.at(diffName));
		if (emisName != "" && textures.find(emisName) != textures.end())
			models.at(emisName).SetEmissionTexture(&textures.at(emisName));
		if (specName != "" && textures.find(specName) != textures.end())
			models.at(resName).SetSpecularTexture(&textures.at(specName));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not create: " << resName << std::endl;
	}
}

void ResourceManager::LoadShader(std::string resName, std::string vertPath, std::string fragPath, std::string geomPath) {
	try
	{
		shaders.emplace(resName, Shader(vertPath.c_str(), fragPath.c_str(), geomPath.c_str()));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not create: " << resName << std::endl;
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