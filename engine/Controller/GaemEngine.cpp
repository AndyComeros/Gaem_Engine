#include "GaemEngine.h"

GameEngine& GameEngine::Get() {

	static GameEngine e_instance;
	return e_instance;
}

GameEngine::GameEngine() :
	deltaTime(0.0),
	fps(0.0),
	prevTime(0.0)
{
	//init window and glfw.
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	scene.camera.aspectRatio = (float)wWidth / (float)wHeight;

	//set defaults for input etc [temp]			should be done by the game
	inputMngr.AddKey(65);//a
	inputMngr.AddKey(68);//d
	inputMngr.AddKey(87);//w
	inputMngr.AddKey(83);//s
	inputMngr.AddKey(67);//c
	inputMngr.AddKey(256);//escape

	inputMngr.setCamera(scene.camera);
	inputMngr.setWindow(window);
	//set defaults for input etc

	//callbacks
	glfwSetFramebufferSizeCallback(window,ResizeCallback);
	glfwSetCursorPosCallback(window, inputMngr.GlfwMouseCallback);
	glfwSetKeyCallback(window, inputMngr.GlfwKeyCallback);
	glfwSetScrollCallback(window, inputMngr.GlfwScrollCallback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
}

GameEngine::~GameEngine() {
	//do some cleanup
	glfwTerminate();
}

//start main loop
void GameEngine::Run() {
	
	scene.camera.position.y = GameEngine::Get().terrain->GetHeight(scene.camera.position.x, scene.camera.position.z) + 3;
	Renderer::SetLightUniforms(scene.lights,renderer.GetShader());
	//temp should be set with to the player by another means
	inputMngr.setPlayer(&scene.gameObjects[2]);
	//temp inneffient light setup. need a recource manager for shaders.
	for (int i = 0; i < scene.gameObjects.size(); i++) {
		if (scene.gameObjects[i].shader) {
			Renderer::SetLightUniforms(scene.lights, *scene.gameObjects[i].shader);
		}
	}


	isRunning = true;

	deltaTime = 0.0;
	prevTime = 0.0;

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

		glfwPollEvents();

		inputMngr.KeyActions(deltaTime);

		renderer.Draw(scene);
		glfwSwapBuffers(window);
		
	}

	//cleanup
	glfwDestroyWindow(window);
}

double GameEngine::DeltaTime() {
	return deltaTime;
}

void GameEngine::ResizeCallback(GLFWwindow* window, int width, int height) {

	Scene& s = GameEngine::Get().scene;
	s.camera.aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	GameEngine::Get().renderer.Draw(s);
}