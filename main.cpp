#include <iostream>.
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <vector>//temp

#include "engine/Model/Graphics/GameAssetFactory.h"

//temp
void pretend_factory();

int main(void)
{
	GameAssetFactory::GetInstance()->ReadInAssets("AssetDictionary.csv");

	//factory populates scene before running game.
	//can also manipulate scene during runtime
	pretend_factory();

	//run
	GameEngine::Get().Run();
	
}

void pretend_factory(){	//setup test scene, factory should do this normally.
	//get reference to 'Model' part of design pattern
	Scene& scene = GameEngine::Get().scene;
	std::vector<GameObject>& objects = GameEngine::Get().scene.gameObjects;
	Lights& lights = GameEngine::Get().scene.lights;

	//load data
	//set skybox
	std::vector<std::string> textures_faces = {
		"resources/textures/skybox/Right.png",
		"resources/textures/skybox/Left.png",
		"resources/textures/skybox/Top.png",
		"resources/textures/skybox/Bottom.png",
		"resources/textures/skybox/Front.png",
		"resources/textures/skybox/Back.png",
	};
	scene.skybox = new CubeMap(textures_faces);

	//create 3D data
	Model3D* arcadeModel = new Model3D("resources/models/untitled2022/Arcade.obj");
	arcadeModel->setDiffuseTexture("resources/models/untitled2022/Arcade.png");

	GameObject arcade;
	arcade.position = { 0,0,0 };
	arcade.model_data = arcadeModel;
  
	scene.gameObjects.push_back(GameAssetFactory::GetInstance()->CreateGameObject("c01"));

	scene.camera.position = { -2,0.5,0 }; 

}
