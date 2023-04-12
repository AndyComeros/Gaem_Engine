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

	//callbacks
	glfwSetKeyCallback(window, inputMngr.GlfwKeyCallback);
	glfwSetFramebufferSizeCallback(window,ResizeCallback);
	glfwSetCursorPosCallback(window, mouse_callback);
}

GameEngine::~GameEngine() {
	//do some cleanup
	glfwTerminate();
}

//start main loop
void GameEngine::Run() {

	Renderer::SetLightUniforms(scene.lights,renderer.GetShader());

	//temp inneffient light setup. need a recource manager for shaders.
	for (int i = 0; i < scene.gameObjects.size(); i++) {
		if (scene.gameObjects[i].shader) {
			Renderer::SetLightUniforms(scene.lights, *scene.gameObjects[i].shader);
		}
	}

	isRunning = true;

	deltaTime = 0.0;
	prevTime = 0.0;


	//[TOREMOVE]  TEMP TEMP REMOVE LATER
	inputMngr.InputManagerInitActions();

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

		scene.physics.StepPhysics();
		scene.physics.updateGameObjects(scene.gameObjects);
		//scene.camera.position = scene.gameObjects[1].position;

		inputMngr.KeyActions();
		//Lab4Input();
		glfwPollEvents();

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


void GameEngine::Lab4Input() {
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	Camera& cam = GameEngine::Get().scene.camera;
	glm::vec3 up = { 0,1,0 };
	float moveSpeed = 100 * GameEngine::Get().DeltaTime();
	float lookSpeed = 100 * GameEngine::Get().DeltaTime();


	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		cam.position += glm::normalize(glm::cross(up, cam.right)) * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		cam.position -= glm::normalize(glm::cross(up, cam.right)) * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		cam.position -= cam.right * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		cam.position += cam.right * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		cam.position += up * moveSpeed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		cam.position -= up * moveSpeed;

	//if escape pressed, close context window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}

	//cam.position.y = GameEngine::Get().terrain->GetHeight(cam.position.x,cam.position.z) + 3;
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
		GameEngine::Get().renderer.wireFrame = !GameEngine::Get().renderer.wireFrame;

}


float lastX = 250, lastY = 250;
void GameEngine::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	Camera& cam = GameEngine::Get().scene.camera;

	float xoffset = xpos - GameEngine::Get().lastX;
	float yoffset = GameEngine::Get().lastY - ypos;
	GameEngine::Get().lastX = xpos;
	GameEngine::Get().lastY = ypos;

	float sensitivity = 0.1f;
	xoffset *= (sensitivity);
	yoffset *= (sensitivity);

	cam.rotation.y += xoffset;
	cam.rotation.x += yoffset;

	if (cam.rotation.x > 89.0f)
		cam.rotation.x = 89.0f;
	if (cam.rotation.x < -89.0f)
		cam.rotation.x = -89.0f;

}
