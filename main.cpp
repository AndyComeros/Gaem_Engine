#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <TerrainManager.h>

int main(void)
{
	GameEngine::Get();

	std::vector<std::string> textures_faces = {
		"resources/textures/skybox/Synthwave2/Right.png",
		"resources/textures/skybox/Synthwave2/Left.png",
		"resources/textures/skybox/Synthwave2/Top.png",
		"resources/textures/skybox/Synthwave2/Bottom.png",
		"resources/textures/skybox/Synthwave2/Front.png",
		"resources/textures/skybox/Synthwave2/Back.png"
	};
	GameEngine::Get().scene.skybox = new CubeMap(textures_faces);

	//Model arcadeModel("resources/models/untitled2022/Arcade.obj");
	//arcadeModel.SetDiffuseTexture("resources/models/untitled2022/Arcade.png");

	//GameObject go;
	//go.model_data = &arcadeModel;


	//GameEngine::Get().scene.gameObjects.push_back(go);

	GameEngine::Get().Run();
}
