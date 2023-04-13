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
	guirenderer.Init(window);

	//scene camera settings
	scene.camera.aspectRatio = (float)wWidth / (float)wHeight;

	inputMngr.setCamera(scene.camera);
	inputMngr.setWindow(window);
	//set defaults for input etc

	//callbacks
	glfwSetKeyCallback(window, inputMngr.GlfwKeyCallback);
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

	//expose to lua
	luaManager.Expose_Engine();
	luaManager.Expose_CPPReference("scene", scene);
	luaManager.RunInitMethod();
	
	//set light uniforms
	auto it = ResourceManager::Get().ShaderBegin();
	auto end = ResourceManager::Get().ShaderEnd();
	for (it; it != end; it++) {
		std::cout << "Set shader: " << it->first << std::endl;
		Renderer::SetLightUniforms(scene.lights, *it->second);
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

		scene.physics.UpdateGameObjects(scene.gameObjects);
		scene.physics.StepPhysics();
		luaManager.RunUpdateMethod(deltaTime);

		renderer.Draw(scene);
		scene.physics.DrawDebug(&scene.camera, ResourceManager::Get().GetShader("physics"));
		guirenderer.Draw();
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
