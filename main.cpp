#include <iostream>
#include <GaemEngine.h>

int main(void)
{
	//Setup Lights
	Scene& scene = GameEngine::Get().scene;
	//scene.lights.ambientLight = { 0.1,0.1,0.1 };
	//scene.lights.directionLights.push_back({ { -0.7,0.5,-1 }, { 0.7,0.1,0.5 }, { 0.5,0.3,0.05 } });

	//setup physics
	scene.physics.CreatePhysicsWorld();
	scene.physics.ToggleDebugDisplay();

	scene.physics.SetTimeStep(60);

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

	Terrain terrain("resources/textures/heightmap/heightmap2048.png", 10, 5, 10);
	terrain.SetTextureScale(5);

	Shader* terrainShader = new Shader("resources/shaders/Default.vert", "resources/shaders/Terrain/Terrain.frag", "");
	terrain.shader = terrainShader;

	terrain.SetTextures(
		{
			new Texture("resources/textures/terrain/water.jpg"),
			new Texture("resources/textures/terrain/dirt.png"),
			new Texture("resources/textures/terrain/grass.png"),
			new Texture("resources/textures/terrain/rock.png"),
			new Texture("resources/textures/terrain/snow.jpg")
		},
		new Texture("resources/textures/terrain/black.png")
	);

	terrain.model_data->SetSpecularTexture("resources/textures/tile_Specular.png");

	terrain.SetTextureHeights({ -20,-10,0,10,100 });
	terrain.SetID(1);
	terrain.position.y = 0;
	scene.physics.AddRigidBody(terrain);
	scene.physics.AddRigidBodyColliderBox(terrain, Vector3(100000, 1, 100000));
	scene.physics.ModRigidBodyType(terrain, STAT);
	scene.gameObjects.push_back(terrain);

	for (int i = 0; i < 20; i++)
	{
		GameObject* arcade = new GameObject();
		arcade->model_data = new Model("resources/models/untitled2022/Arcade.obj");
		arcade->model_data->SetDiffuseTexture("resources/models/untitled2022/Arcade.png");
		arcade->position.y = i;
		arcade->shader = ResourceManager::Get().GetShader("default");
		scene.physics.AddRigidBody(*arcade);
		scene.physics.ModRigidBodyType(*arcade, DYNA);
		scene.physics.AddRigidBodyColliderBox(*arcade, Vector3(2, 2, 2));
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
	scene.camera.position.x = terrain.GetSize() / 2.0;
	scene.camera.position.z = terrain.GetSize() / 2.0;
	scene.camera.farPlane = 2000;

	//Run the game
	GameEngine::Get().Run();
}
