#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <TerrainManager.h>

int main(void)
{
	//Setup Lights
	Scene& scene = GameEngine::Get().scene;
	scene.lights.ambientLight = { 0.1,0.1,0.1 };
	scene.lights.directionLights.push_back({ { -0.7,0.5,-1 }, { 0.85,0.85,1 }, { 0.95,0.1,0.6 } });

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
	std::vector<float> heightMap = TerrainManager::GenHeightMapFaultFormation(256,50,0,10,0.4,0.4);
	//Texture* heightMap = new Texture("resources/textures/heightmap/heightmap128.png");
	Terrain terrain(heightMap);
	Shader* terrainShader = new Shader("resources/shaders/Default.vert", "resources/shaders/Terrain/Terrain.frag", nullptr);
	terrain.shader = terrainShader;
	terrain.SetTextureScale(50);
	terrain.SetTextures(
		{
			new Texture("resources/textures/terrain/water.jpg"),
			new Texture("resources/textures/terrain/sand.jpg"),
			new Texture("resources/textures/terrain/grass.jpg"),
			new Texture("resources/textures/terrain/rock.jpg"),
			new Texture("resources/textures/terrain/snow.jpg")
		},
		new Texture("resources/textures/terrain/detailMap.png")
	);

	terrain.SetTextureHeights({0,10,20,30,40});
	
	scene.gameObjects.push_back(terrain);
	GameEngine::Get().terrain = &terrain;

	//TEST ARCADE MACHINE
	GameObject* arcade = new GameObject();
	arcade->model_data = new Model("resources/models/untitled2022/Arcade.obj");
	arcade->model_data->SetDiffuseTexture("resources/models/untitled2022/Arcade.png");
	arcade->position.x = terrain.GetSize() / 2.0;
	arcade->position.z = terrain.GetSize() / 2.0;
	arcade->position.y = terrain.GetHeight(arcade->position.x, arcade->position.z);
	scene.gameObjects.push_back(*arcade);

	//Setup Camera
	scene.camera.FOV = 75;
	scene.camera.position.x = terrain.GetSize() / 2.0;
	scene.camera.position.z = terrain.GetSize() / 2.0;
	scene.camera.farPlane = 2000;

	//Run the game
	GameEngine::Get().Run();
}
