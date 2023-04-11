#include <iostream>
#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <GaemEngine.h>

#include <TerrainManager.h>

int main(void)
{
	std::cout << "HERE!1";
	Model* arcadeModel;// = new Model("resources/models/untitled2022/Arcade.obj");
	arcadeModel = new Model("resources/models/untitled2022/Arcade.obj");

	GameEngine::Get().Run();
}
