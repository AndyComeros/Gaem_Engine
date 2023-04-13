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

void InputManager::KeyActions(float deltatime)
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
				//move player
				_Player->position.z += 100 * deltatime;
				_Player->rotation.y = 90.0f;
				_Camera->CalaulateCamPos(_Player->position);
				break;
			case GLFW_KEY_A:
				_Player->position.x += 100 * deltatime;
				_Player->rotation.y = 180;
				_Camera->CalaulateCamPos(_Player->position);
				break;
			case GLFW_KEY_S:
				_Player->position.z -= 100 * deltatime;
				_Player->rotation.y = -90.0f;
				_Camera->CalaulateCamPos(_Player->position);
				break;
			case GLFW_KEY_D:
				_Player->position.x -= 100 * deltatime;
				_Player->rotation.y = 0.0f;
				_Camera->CalaulateCamPos(_Player->position);
				break;
			case GLFW_KEY_C:
				//causes circle inhertince
				//GameEngine::Get().renderer.wireFrame = !GameEngine::Get().renderer.wireFrame;
				break;
			case GLFW_KEY_SPACE:
				break;
			case GLFW_KEY_ESCAPE:
				glfwSetWindowShouldClose(_Window, true);
				break;
			default:
				break;
			}
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
		inputMap[key] = true;
	else if (action == GLFW_RELEASE)
		inputMap[key] = false;
}
