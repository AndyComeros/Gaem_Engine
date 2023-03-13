#include "GaemEngine.h"

GameEngine& GameEngine::Get() {

	static GameEngine e_instance;
	return e_instance;
}

GameEngine::GameEngine(): 
	deltaTime(0.0),
	fps(0.0)
{
	//init window and glfw and opengl.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	glfwWindowHint(GLFW_SAMPLES, 4);
	window = glfwCreateWindow(wWidth, wHeight, "Engine", NULL, NULL);

	if (!window)
	{
		std::cout << "ERROR Could not initalize window." << std::endl;
		glfwTerminate();
		return;
	}
	glfwMakeContextCurrent(window);

	//initialize glad before we can use openGL
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: Could not load glad" << std::endl;
		return;
	}

	//init renderer
	

	//set defaults for input etc
}


GameEngine::~GameEngine() {
	//do some cleanup
	glfwTerminate();
}

void GameEngine::Init() {
	glfwInit();
}

//start main loop
void GameEngine::Run() {

	//init renderer
	renderer.Init(window);

	//main loop./
	while (!glfwWindowShouldClose(window))
	{
		//Renderer.Draw();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//cleanup
	glfwDestroyWindow(window);
}