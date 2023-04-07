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

	//set defaults for input etc

	//callbacks
	glfwSetFramebufferSizeCallback(window,ResizeCallback);
	glfwSetKeyCallback(window, Lab4Input);
}

GameEngine::~GameEngine() {
	//do some cleanup
	glfwTerminate();
}

//start main loop
void GameEngine::Run() {
	
	scene.camera.position.y = GameEngine::Get().terrain->GetHeight(scene.camera.position.x, scene.camera.position.z) + 3;

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

	//main loop
	while (!glfwWindowShouldClose(window))
	{
		float time = glfwGetTime();
		deltaTime = time - prevTime;
		prevTime = time;

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

void GameEngine::Lab4Input(GLFWwindow* window, int key, int scancode, int action, int mods) {

	Camera& cam = GameEngine::Get().scene.camera;
	glm::vec3 up = { 0,1,0 };
	float moveSpeed = 100 * GameEngine::Get().DeltaTime();
	float lookSpeed = 100 * GameEngine::Get().DeltaTime();

	switch (key)
	{
	case GLFW_KEY_W :
		cam.position += glm::normalize(glm::cross(up, cam.rightVec)) * moveSpeed;
		break;
	case GLFW_KEY_A:
		cam.position -= cam.rightVec * moveSpeed;
		break;
	case GLFW_KEY_S:
		cam.position -= glm::normalize(glm::cross(up, cam.rightVec)) * moveSpeed;
		break;
	case GLFW_KEY_D:
		cam.position += cam.rightVec * moveSpeed;
		break;
	case GLFW_KEY_SPACE:
		cam.position += up * moveSpeed;
		break;
	case GLFW_KEY_LEFT_SHIFT:
		cam.position -= up * moveSpeed;
		break;
	case GLFW_KEY_UP:
		cam.rotation.x += lookSpeed;
		break;
	case GLFW_KEY_DOWN:
		cam.rotation.x -= lookSpeed;
		break;
	case GLFW_KEY_LEFT:
		cam.rotation.y -= lookSpeed;
		break;
	case GLFW_KEY_RIGHT:
		cam.rotation.y += lookSpeed;
		break;
	default:
		break;
	}

	//cam.position.y = GameEngine::Get().terrain->GetHeight(cam.position.x,cam.position.z) + 3;

	if (key == GLFW_KEY_C && action == GLFW_PRESS) {
		GameEngine::Get().renderer.wireFrame = !GameEngine::Get().renderer.wireFrame;
	}

}