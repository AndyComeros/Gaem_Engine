#include "InputManager.h"
#include <GaemEngine.h>

InputManager& InputManager::Get()
{
	static InputManager instance;
	return instance;
}

void InputManager::BindKey(std::string action, int newKey)
{
	inputMap[action] = keyBinding{ newKey, false };
}

void InputManager::RemoveKey(std::string action)
{
	inputMap[action] = keyBinding{ -1, false };
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

void InputManager::BindAction(std::string action, actionPTR actionFunc)
{
	_ActionMap[action] = actionFunc;
}

void InputManager::RemoveAction(std::string action)
{
	_ActionList.remove(action);
	inputMap.erase(action);
	_ActionMap.erase(action);
}

void InputManager::AddAction(std::string action)
{
	_ActionList.push_back(action);
	inputMap.insert({ action, keyBinding{ -1, false } });
	_ActionMap.insert({ action, nullptr });
}

void InputManager::KeyActions(float deltatime)
{
	for (auto action : _ActionList)
	{
		for (auto key : inputMap)
		{
			keyBinding bind = key.second;
			if (bind.state == true)
			{
				if (key.first == action)
					_ActionMap[action]();
			}
		}
	}
}


void InputManager::mouseCallback(GLFWwindow* window, double xPos, double yPos)
{
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xoffset = xPos - lastX;
	float yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
{

}

void InputManager::SetMouseLock(bool visable)
{
	if(visable)
	{
		glfwSetInputMode(GameEngine::Get().window, GLFW_CURSOR, GLFW_CURSOR);
	}
	else
	{
		glfwSetInputMode(GameEngine::Get().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}
}

glm::vec2 InputManager::GetMousePostion()
{
	double xPos, yPos;
	glfwGetCursorPos(GameEngine::Get().window, &xPos, &yPos);
	return glm::vec2{xPos, yPos};
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
