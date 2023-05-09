#include "GaemEngine.h"
#include <string.h>
#include <iostream>

GameEngine& GameEngine::Get() {

	static GameEngine e_instance;
	return e_instance;
}

GameEngine::GameEngine() 
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

	inputMngr.Init(window);
	renderer.Init(window);
	guirenderer.Init(window);
	

	//scene camera settings
	scene.camera.aspectRatio = (float)wWidth / (float)wHeight;

	//callbacks
	glfwSetFramebufferSizeCallback(window, ResizeCallback);
}

GameEngine::~GameEngine() {
	//do some cleanup
	
	glfwTerminate();
}

//start main loop
void GameEngine::Run() {

	//expose to lua
	luaManager.Expose_Engine();
	luaManager.Expose_CPPReference("scene", scene);
	luaManager.Expose_CPPReference("physics", scene.physics);
	luaManager.Expose_CPPReference("renderer",	renderer);
	luaManager.Expose_CPPReference("GUI", guirenderer);
	luaManager.RunInitMethod();
	
	//set light uniforms
	auto it = ResourceManager::Get().ShaderBegin();
	auto end = ResourceManager::Get().ShaderEnd();
	for (it; it != end; it++) {
		Renderer::SetLightUniforms(scene.lights, *it->second);
	}

	isRunning = true;
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		// timer
		double currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;
		accumulator += deltaTime;
    
		glfwPollEvents();

		scene.physics.StepPhysics(deltaTime);
		scene.physics.UpdateGameObjects(scene.gameObjects);
		luaManager.RunUpdateMethod(deltaTime);

		inputMngr.KeyActions(deltaTime);

		renderer.Draw(scene, deltaTime);
		scene.physics.DrawDebug(&scene.camera, ResourceManager::Get().GetShader("physics"));
		guirenderer.Draw();
		glfwSwapBuffers(window);

	}
	isRunning = false;

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
	GameEngine::Get().renderer.Draw(s, GameEngine::Get().deltaTime);
  }
