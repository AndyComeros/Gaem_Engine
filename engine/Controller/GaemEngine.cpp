#include "GaemEngine.h"

GameEngine& GameEngine::Get() {

	static GameEngine e_instance;
	return e_instance;
}

GameEngine::GameEngine() :
	deltaTime(0.0),
	fps(0.0)
{
	//init window and glfw.
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

	//glad required to access GL functions
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "ERROR: Could not load glad" << std::endl;
		return;
	}

	//init renderer
	renderer.Init(window);

	//scene camera settings
	scene.camera.aspectRatio = wWidth / wHeight;

	//set defaults for input etc [temp]			should be done by the game
	inputMngr.LoadKeyConfig();
	inputMngr.AddKey(65);//a
	inputMngr.AddKey(68);//d
	inputMngr.AddKey(87);//w
	inputMngr.AddKey(83);//s

	//set GLFW callback
}


GameEngine::~GameEngine() {
	//do some cleanup
	glfwTerminate();
}

//start main loop
void GameEngine::Run() {

	isRunning = true;

	glfwSetKeyCallback(window, &InputManager::GlfwKeyCallback);

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		inputMngr.KeyActions();
		renderer.Draw(scene);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//cleanup
	glfwDestroyWindow(window);
}
