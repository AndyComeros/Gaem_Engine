#pragma once

#include <vector>
#include <map>
#include <fstream>

#include <GLFW/glfw3.h>
#include <Camera.h>
#include <GameObject.h>

class InputManager
{
	public:
		static InputManager& getInstance()	//singleton
		{
			static InputManager instance;
			return instance;
		}

		void AddKey(int newKey);
		void RemoveKey(int keyToDel);
		bool GetKeyState(int keyCheck);

		void KeyActions(float deltatime);

		static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			getInstance().GlfwKeyCallbackDispatch(window, key, scancode, action, mods);
		}

		void GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);

		static void GlfwMouseCallback(GLFWwindow* window, double xpos, double ypos)
		{
			getInstance().mouseCallback(window, xpos, ypos);
		}

		void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		static void GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			getInstance().ScrollCallback(window, xoffset, yoffset);
		}

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void setCamera(Camera &camera) { _Camera = &camera; }
		void setWindow(GLFWwindow* window) { _Window = window; }
		void setPlayer(GameObject* player) { _Player = player; }

	private:
		//std::map<int, std::map<int, bool>> inputOuterMap;
		InputManager(){}				
		InputManager(InputManager const&);		//prevent copies
		void operator=(InputManager const&);	//prevent assignments

		Camera* _Camera;
		GameObject* _Player = new GameObject();
		GLFWwindow* _Window;

		bool firstMouse = true;
		float lastX = 1920 / 2.0f;
		float lastY = 1080 / 2.0f;


		std::map<int, bool> inputMap;
		
};