#include "ResourceManager.h"


ResourceManager& ResourceManager::Get() {
	
	static ResourceManager r_instance;
	return r_instance;
}

ResourceManager::ResourceManager(){

		//default shader
	shaders.emplace("default", new Shader("resources/shaders/Default.vert", "resources/shaders/Default.frag", ""));
		//default physics debug
	shaders.emplace("physics", new Shader("resources/shaders/Physics_Debug/Physics.vert", "resources/shaders/Physics_Debug/Physics.frag", ""));
		//default terrain shader
	shaders.emplace("terrain", new Shader("resources/shaders/Default.vert", "resources/shaders/terrain/Terrain.frag", ""));
		//default texture
	textures.emplace("default", new Texture("resources/textures/default.png"));
}

ResourceManager::~ResourceManager(){}


GameObject ResourceManager::CreateGameObject(std::string objectName, std::string modelName, std::string shaderName) {
	GameObject gameObject;
	gameObject.name = objectName;
	gameObject.SetID(IDIndex);
	IDIndex++;

	gameObject.model_data = GetModel(modelName);

	if (!shaderName.empty()) {
		gameObject.shader = GetShader(shaderName);
	}
	else if (shaders.find("default") != shaders.end()) {
		gameObject.shader = shaders.at("default");
	}

	return gameObject;
}

Terrain ResourceManager::CreateTerrain(std::string terrainName, std::string heightMapName, std::vector<std::string> layerTextures, std::string detailName, float scaleX, float scaleY, float scaleZ) {
	
	Terrain terrain(textures.at(heightMapName),scaleX,scaleY,scaleZ);
	
	if (shaders.find("terrain") != shaders.end())
		terrain.shader = shaders.at("terrain");

	std::vector<Texture*> layers;
	for (int i = 0; i < layerTextures.size(); i++)
		layers.emplace_back(textures.at(layerTextures[i]));

	terrain.SetTextures(layers,textures.at(detailName));

	terrain.name = terrainName;
	terrain.SetID(IDIndex);
	IDIndex++;

	return terrain;
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

void ResourceManager::LoadCubemap(std::string resName, std::string right, std::string left, std::string top, std::string bottom, std::string front, std::string back) {
	try
	{
		std::vector<std::string> sides({right,left,top,bottom,front,back});
		cubemaps.emplace(resName, new CubeMap(sides));
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

CubeMap* ResourceManager::GetCubeMap(std::string resName) {
	CubeMap* cubemap;
	try
	{
		cubemap = cubemaps.at(resName);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Cubemap: '" << resName << "' does not exist: " << e.what() << std::endl;
		cubemap = nullptr;
	}
	return cubemap;

}