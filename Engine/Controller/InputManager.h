#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>
#include <Camera.h>
#include <GameObject.h>

class GaemEngine;

class InputManager
{
	public:
		void InputManagerInitActions();

		static InputManager& getInstance()	//singleton
		{
			static InputManager instance;
			return instance;
		}

		void BindKey(std::string action, int newKey);
		void RemoveKey(std::string action);
		bool GetKeyState(std::string action);

		void KeyActions(float deltatime);

		static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
			getInstance().GlfwKeyCallbackDispatch(window, key, scancode, action, mods);
		}
		void GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);


		void EnableKey(int key);
		void DisableKey(int key);

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
		InputManager() {}
		InputManager(InputManager const&);		//prevent copies
		void operator=(InputManager const&);	//prevent assignments

		struct keyBinding { int key; bool state; };

		std::map<std::string, keyBinding> inputMap;

		Camera* _Camera;
		GameObject* _Player = new GameObject();
		GLFWwindow* _Window;

		bool firstMouse = true;
		float lastX = 1920 / 2.0f;
		float lastY = 1080 / 2.0f;

		
};