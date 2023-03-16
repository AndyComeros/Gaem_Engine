#include "InputManager.h"
#include <iostream>

void InputManager::AddKey(int newKey)
{
	inputMap.emplace(newKey, false);
}

void InputManager::RemoveKey(int keyToDel)
{
	inputMap.erase(keyToDel);
}
/*
void InputManager::ToggleKey(int keyToTog)												
{
	inputMap[keyToTog] = !inputMap[keyToTog];
}*/

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
				 case GLFW_KEY_A:  
					 std::cout << "KEY a PRESSED" << std::endl;
					 break;
				 case GLFW_KEY_W:
					 std::cout << "KEY w PRESSED" << std::endl;
					 break;
				 default:
					 std::cout << "no key pressed" << std::endl;
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
