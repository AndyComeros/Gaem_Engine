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

	if(!shaderName.empty())
		gameObject.shader = GetShader(shaderName);

	return gameObject;
}

void ResourceManager::LoadTexture(std::string resName, std::string fileName) {
	try
	{
		textures.emplace(resName, new Texture(fileName.c_str()));
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not create: " << resName << std::endl;
	}
}

void ResourceManager::LoadModel(std::string resName, std::string fileName, std::string diffName, std::string emisName, std::string specName) {
	try
	{
		Model* model = new Model(fileName.c_str());

		//textures
		if (textures.find(diffName) != textures.end())
			model->SetDiffuseTexture(textures.at(diffName));
		if (textures.find(emisName) != textures.end())
			model->SetEmissionTexture(textures.at(emisName));
		if (textures.find(specName) != textures.end())
			model->SetSpecularTexture(textures.at(specName));

		//model
		models.emplace(resName, model);

		
	}
	catch (const std::exception&)
	{
		std::cout << "Error: Could not create: " << resName << std::endl;
	}
}

void ResourceManager::LoadShader(std::string resName, std::string vertPath, std::string fragPath, std::string geomPath) {
	try
	{
		shaders.emplace(resName, new Shader(vertPath.c_str(), fragPath.c_str(), geomPath.c_str()));
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
		texture = textures.at(resName);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Texture: '" << resName << "' does not exist: " << e.what() << std::endl;
		texture = nullptr;
	}
	return texture;
}

Model* ResourceManager::GetModel(std::string resName) {
	Model* model;
	try
	{
		model = models.at(resName);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Model: '" << resName << "' does not exist: " << e.what() << std::endl;
		model = nullptr;
	}
	return model;
}

Shader* ResourceManager::GetShader(std::string resName) {
	Shader* shader;
	try
	{
		shader = shaders.at(resName);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Shader: '" << resName << "' does not exist: " << e.what() << std::endl;
		shader = nullptr;
	}
	return shader;
}