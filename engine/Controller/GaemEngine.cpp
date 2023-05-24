#include "GaemEngine.h"
#include <string.h>
#include <iostream>

GameEngine& GameEngine::Get() {

	static GameEngine e_instance;
	return e_instance;
}

void GameEngine::ExposeToLua(){

	luaManager.Expose_CPPClass<GameEngine>("GameEngine",
		sol::no_constructor,
		"Time", &GameEngine::Time,
		"DeltaTime", &GameEngine::DeltaTime,
		"Shutdown", &GameEngine::Shutdown,
		"IsSimRunning", &GameEngine::IsSimRunning,
		"SetSimulation", &GameEngine::SetSimulation,
		"scene", &GameEngine::scene
		);
	luaManager.Expose_CPPReference("engine",*this);
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

	//scene camera settings
	scene = new Scene;
	scene->camera.aspectRatio = (float)wWidth / (float)wHeight;

	inputMngr.Init(window);
	renderer.Init(window);
	guirenderer.Init(window);
	aiManager.Init(scene);

	//callbacks
	glfwSetFramebufferSizeCallback(window, ResizeCallback);

	//expose to lua
	ExposeToLua();
	luaManager.Expose_Engine();
	luaManager.Expose_CPPReference("scene", *scene);
	luaManager.Expose_CPPReference("physics", scene->physics);
	luaManager.Expose_CPPReference("renderer", renderer);
	luaManager.Expose_CPPReference("GUI", guirenderer);

	luaManager.RunInitMethod();

	//set light uniforms
	auto it = ResourceManager::Get().ShaderBegin();
	auto end = ResourceManager::Get().ShaderEnd();
	for (it; it != end; it++) {
		Renderer::SetLightUniforms(scene->lights, *it->second);
	}

	//SceneLoader loader;
	//loader.SaveScene(scene,"scene.json");
	//scene = (loader.LoadScene("scene.json"));
	//luaManager.Expose_CPPReference("scene", *scene);
	//luaManager.Expose_CPPReference("physics", scene->physics);
	//aiManager.Init(scene);
}

GameEngine::~GameEngine() {
	//do some cleanup

}

//start main loop
void GameEngine::Run() {

	isRunning = true;
	//main loop
	while (!glfwWindowShouldClose(window))
	{
		// timer
		double currentFrameTime = glfwGetTime();
		deltaTime = currentFrameTime - previousFrameTime;
		previousFrameTime = currentFrameTime;
		accumulator += deltaTime;
		
		inputMngr.KeyActions(deltaTime);

		if (simIsRunning) {
			scene->physics.StepPhysics(deltaTime);
			scene->physics.UpdateGameObjects(scene->gameObjects);
			aiManager.UpdateAgents(deltaTime);
		}
		else {
			deltaTime = 0.0f;
		}

		renderer.Draw(*scene, deltaTime);
		scene->physics.DrawDebug(&scene->camera, ResourceManager::Get().GetShader("physics"));
		luaManager.RunUpdateMethod(deltaTime);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	isRunning = false;

	//cleanup
	glfwDestroyWindow(window);
	glfwTerminate();
}

double GameEngine::Time()
{
	return glfwGetTime();
}

double GameEngine::DeltaTime() {
	return deltaTime;
}

void GameEngine::ResizeCallback(GLFWwindow* window, int width, int height) {

	Scene& s = *GameEngine::Get().scene;
	s.camera.aspectRatio = (float)width / (float)height;
	glViewport(0, 0, width, height);
	GameEngine::Get().renderer.Draw(s, GameEngine::Get().deltaTime);
}

void GameEngine::Shutdown()
{
	isRunning = false;
	glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void GameEngine::SetSimulation(bool isRun)
{
	simIsRunning = isRun;
}

bool GameEngine::IsSimRunning()
{
	return simIsRunning;
}

