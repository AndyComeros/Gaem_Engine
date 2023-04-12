#pragma once

#include <vector>
#include <map>
#include <iostream>
#include <string>

#include <GLFW/glfw3.h>

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

		void KeyActions();

		static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods){
			getInstance().GlfwKeyCallbackDispatch(window, key, scancode, action, mods);
		}
		void GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);

		void EnableKey(int key);
		void DisableKey(int key);

	private:
		//std::map<int, std::map<int, bool>> inputOuterMap;
		InputManager() {}
		InputManager(InputManager const&);		//prevent copies
		void operator=(InputManager const&);	//prevent assignments

		struct keyBinding { int key; bool state; };

		std::map<std::string, keyBinding> inputMap;

		
};