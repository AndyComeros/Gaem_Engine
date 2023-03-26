#include "InputManager.h"

void InputManager::AddKey(int newKey)
{
	inputMap.emplace(newKey, false);
}

void InputManager::RemoveKey(int keyToDel)
{
	inputMap.erase(keyToDel);
}

bool InputManager::GetKeyState(int keyCheck)
{
	std::map<int, bool>::iterator it = inputMap.find(keyCheck);
	if (it != inputMap.end())
		return it->second;
}

void InputManager::KeyActions()
{
	for (auto key : inputMap)
	{
		if (key.second == true)
		{			
				//------------------------------//
				//  key press action goes here  //
				//------------------------------//
			switch (key.first)
			{
				 case GLFW_KEY_W:
					 break;
				 case GLFW_KEY_A:  
					 break;
				 case GLFW_KEY_S:
					 break;
				 case GLFW_KEY_D:
					 break;
				 case GLFW_KEY_SPACE:
					 break;
				 default:
					 break;
			}
		}
	}
}


void InputManager::GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
		inputMap[key] = true;
	else if (action == GLFW_RELEASE)
		inputMap[key] = false;
}
