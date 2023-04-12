#include "InputManager.h"
#include <GaemEngine.h>

void InputManager::InputManagerInitActions()
{
	/*
	keyBinding init = { -1, false };
	inputMap.emplace("forward", init);
	inputMap.emplace("left", init);
	inputMap.emplace("right", init);
	inputMap.emplace("backward", init);
	inputMap.emplace("shoot", init);
	*/
	inputMap.emplace("forward", keyBinding{GLFW_KEY_W, false});
	inputMap.emplace("left", keyBinding{ GLFW_KEY_A, false });
	inputMap.emplace("right", keyBinding{ GLFW_KEY_D, false });
	inputMap.emplace("backward", keyBinding{ GLFW_KEY_S, false });
	inputMap.emplace("up", keyBinding{ GLFW_KEY_E, false });
	inputMap.emplace("down", keyBinding{ GLFW_KEY_Q, false });
	inputMap.emplace("shoot", keyBinding{ GLFW_KEY_SPACE, false });
	inputMap.emplace("wireframemode", keyBinding{ GLFW_KEY_C, false });
	inputMap.emplace("quit", keyBinding{ GLFW_KEY_ESCAPE, false });
}

void InputManager::BindKey(std::string action, int newKey)
{
	inputMap[action] = keyBinding{ newKey, false };
}

void InputManager::RemoveKey(std::string action)
{
	inputMap[action] = keyBinding{ -1,false };
}

bool InputManager::GetKeyState(std::string action)
{
	std::map<std::string, keyBinding>::iterator it = inputMap.find(action);
	if (it != inputMap.end())
	{
		keyBinding bind = it->second;
		return bind.state;
	}
}

void InputManager::KeyActions()
{
	glfwSetInputMode(GameEngine::Get().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//[TOREMOVE] TEMP 
	Camera& cam = GameEngine::Get().scene.camera;
	glm::vec3 up = { 0,1,0 };
	float moveSpeed = 100 * GameEngine::Get().DeltaTime();
	float lookSpeed = 100 * GameEngine::Get().DeltaTime();

	for (auto key : inputMap)
	{	
		keyBinding bind = key.second; 
		if (bind.state == true)
		{			
			if (key.first == "forward")
				cam.position += glm::normalize(glm::cross(up, cam.right)) * moveSpeed;
			if (key.first == "left")
				cam.position -= cam.right * moveSpeed;
			if (key.first == "right")
				cam.position += cam.right * moveSpeed;
			if (key.first == "backward")
				cam.position -= glm::normalize(glm::cross(up, cam.right)) * moveSpeed;
			if (key.first == "up")
				cam.position += up * moveSpeed;
			if (key.first == "down")
				cam.position -= up * moveSpeed;
			if (key.first == "shoot")
				std::cout << "shoot" << std::endl;
			if (key.first == "wireframemode")
				GameEngine::Get().renderer.wireFrame = !GameEngine::Get().renderer.wireFrame;
			if (key.first == "quit")
				glfwSetWindowShouldClose(GameEngine::Get().window, true);
		}
	}
}

void InputManager::GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS) 
		EnableKey(key);
	else if (action == GLFW_RELEASE)
		DisableKey(key);
}

void InputManager::EnableKey(int key) 
{
	for (auto it : inputMap)
	{
		keyBinding& bind = inputMap[it.first]; 
		if (bind.key == key)
			bind.state = true; 
	}
}

void InputManager::DisableKey(int key)
{
	for (auto it : inputMap)
	{
		keyBinding& bind = inputMap[it.first];
		if (bind.key == key)
			bind.state = false;
	}
}


void InputManager::operator=(InputManager const&)
{
}
