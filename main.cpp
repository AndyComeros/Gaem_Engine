#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <TerrainManager.h>

int main(void)
{
	//Setup Lights
	Scene& scene = GameEngine::Get().scene;
	//scene.lights.ambientLight = { 0.1,0.1,0.1 };
	//scene.lights.directionLights.push_back({ { -0.7,0.5,-1 }, { 0.7,0.1,0.5 }, { 0.5,0.3,0.05 } });

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
	Texture* heightMap = new Texture("resources/textures/heightmap/heightmap2048.png");

	Terrain terrain("resources/textures/heightmap/heightmap256.png",20,5,20);
	terrain.SetTextureScale(5);

	Shader* terrainShader = new Shader("resources/shaders/Default.vert", "resources/shaders/Terrain/Terrain.frag", nullptr);

	terrain.shader = terrainShader;
	
	terrain.SetTextures(
		{
			new Texture("resources/textures/terrain/rock.png"),
			new Texture("resources/textures/terrain/grass.png"),
		},
		new Texture("resources/textures/terrain/black.png")
	);

	terrain.model_data->SetSpecularTexture("resources/textures/tile_Specular.png");

	terrain.SetTextureHeights({300,500});
	
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
	scene.camera.farPlane = 10000;

	//Run the game
	GameEngine::Get().Run();
}
