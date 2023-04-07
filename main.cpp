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
	scene.lights.directionLights.push_back({ { -1,0.5,-1 }, { 0.85,0.85,1 }, { 1,1,1 } });

	//Set Skybox
	std::vector<std::string> textures_faces = {
		"resources/textures/skybox/Right.png",
		"resources/textures/skybox/Left.png",
		"resources/textures/skybox/Top.png",
		"resources/textures/skybox/Bottom.png",
		"resources/textures/skybox/Front.png",
		"resources/textures/skybox/Back.png",
	};
	scene.skybox = new CubeMap(textures_faces);


	//Create Terrain
	//std::vector<float> heightMap = TerrainManager::GenHeightMapFaultFormation(terrainSize,64,0,10,0.4,0.5);
	Texture* heightMap = new Texture("resources/textures/heightmap/heightmap128.png");
	Terrain terrain(heightMap,10);
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

	terrain.SetTextureHeights({-3,0,2,5,8});
	
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
