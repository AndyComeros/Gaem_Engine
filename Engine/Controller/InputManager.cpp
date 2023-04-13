#include "InputManager.h"
#include <GaemEngine.h>


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

void InputManager::KeyActions(float deltatime)
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


void InputManager::mouseCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;

	lastX = xpos;
	lastY = ypos;

	_Camera->ProcessMouseMovement(xoffset, yoffset, _Player->position);
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{
	_Camera->Distance -= (float)yoffset;
	if (_Camera->Distance < 3.0f)
		_Camera->Distance = 3.0f;
	if (_Camera->Distance > 45.0f)
		_Camera->Distance = 45.0f;

	_Camera->CalaulateCamPos(_Player->position);
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
