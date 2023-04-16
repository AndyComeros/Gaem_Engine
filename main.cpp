#include <iostream>
#include <GaemEngine.h>

int main(void)
{
	//Setup Lights
	Scene& scene = GameEngine::Get().scene;
	//scene.lights.ambientLight = { 0.1,0.1,0.1 };
	//scene.lights.directionLights.push_back({ { -0.7,0.5,-1 }, { 0.7,0.1,0.5 }, { 0.5,0.3,0.05 } });

	//setup physics
	scene.physics.ToggleDebugDisplay();

	//Set Skybox
	std::vector<std::string> textures_faces = {
		"resources/textures/skybox/Synthwave2/Right.png",
		"resources/textures/skybox/Synthwave2/Left.png",
		"resources/textures/skybox/Synthwave2/Top.png",
		"resources/textures/skybox/Synthwave2/Bottom.png",
		"resources/textures/skybox/Synthwave2/Front.png",
		"resources/textures/skybox/Synthwave2/Back.png"
	};
	scene.skybox = new CubeMap(textures_faces);
	
	//Create Terrain
	//std::vector<float> heightMap = TerrainManager::GenHeightMapFaultFormation(256,50,0,10,0.4,0.4);
	//Texture* heightMap = new Texture("resources/textures/heightmap/heightmap128.png");

	Terrain terrain("resources/textures/heightmap/heightmap128.png", 1, 0.1, 1);
	Shader* terrainShader = new Shader("resources/shaders/Default.vert", "resources/shaders/Terrain/Terrain.frag", "");
	terrain.shader = terrainShader;

	terrain.model_data->SetSpecularTexture("resources/textures/tile_Specular.png");

	terrain.SetID(1);
	terrain.position.y = 0;
	
	scene.gameObjects.push_back(terrain);

	scene.physics.AddRigidBody(terrain);
	scene.physics.AddRigidBodyColliderHeightMap(terrain);
	scene.physics.ModRigidBodyType(terrain, STAT);

	
	ResourceManager::Get().LoadTexture("arcade","resources/models/untitled2022/Arcade.png");
	ResourceManager::Get().LoadModel("arcade", "resources/models/untitled2022/Arcade.obj", "arcade", "", "");
	for (int i = 0; i < 20; i++)
	{
		GameObject* arcade = new GameObject();
		arcade->model_data = ResourceManager::Get().GetModel("arcade");
		arcade->position.y = i;
		arcade->shader = ResourceManager::Get().GetShader("default");
		scene.physics.AddRigidBody(*arcade);
		scene.physics.ModRigidBodyType(*arcade, DYNA);
		scene.physics.AddRigidBodyColliderBox(*arcade, Vector3(1, 1, 1));
		arcade->SetID(i+1);
		scene.gameObjects.push_back(*arcade);
	}

	/*
	//TEST ARCADE MACHINE
	GameObject* arcade = new GameObject();
	arcade->model_data = new Model("resources/models/untitled2022/Arcade.obj");
	arcade->model_data->SetDiffuseTexture("resources/models/untitled2022/Arcade.png");
	//arcade->position.x = terrain.GetSize() / 2.0;
	//arcade->position.z = terrain.GetSize() / 2.0;
	arcade->position.y = 0;// terrain.GetHeight(arcade->position.x, arcade->position.z);
	arcade->shader = ResourceManager::Get().GetShader("default");
	scene.physics.AddRigidBody(*arcade);
	scene.physics.ModRigidBodyType(*arcade, DYNA);
	scene.physics.AddRigidBodyColliderBox(*arcade, Vector3(2, 2, 2));
	arcade->SetID(2);
	scene.gameObjects.push_back(*arcade);
	*/

	//Setup Camera
	scene.camera.FOV = 75;


	scene.camera.farPlane = 2000;

	GameEngine::Get().Run();
}
