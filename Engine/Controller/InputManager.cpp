#include "InputManager.h"
#include <iostream>

/*void InputManager::AddInputInnerMap()
{

}*/

void InputManager::AddKey(int newKey)
{
	inputMap.emplace(newKey, false);
}

void InputManager::RemoveKey(int keyToDel)
{
	inputMap.erase(keyToDel);
}

void InputManager::CheckInputLoop()
{
	for (auto key : inputMap)
	{
		if (key.second == true)
		{
			switch (key.first)
			{
			////////////////////////////////
			//  key press action goes here
			////////////////////////////////
				 case 65:  //GLFW_KEY_A
					 std::cout << "KEY a PRESSED" << std::endl;
					 break;
				 default:
					 std::cout << "no key pressed" << std::endl;
					 break;
			}
		}
	}
}

void InputManager::GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		inputMap[key] = true;
	}
	else if (action == GLFW_RELEASE)
	{
		inputMap[key] = false;
	}

}
