#pragma once

#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <string>
#include <GLFW/glfw3.h>
#include <Camera.h>
#include <GameObject.h>

typedef void(*actionPTR)();

class InputManager
{
	public:
		void InputManagerInitActions();

		static InputManager& Get();

		void BindKey(std::string action, int newKey);
		void RemoveKey(std::string action);
		bool GetKeyState(std::string action);

		void BindAction(std::string action, actionPTR actionFunc);
		void RemoveAction(std::string action);

		void KeyActions(float deltatime);

		void GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);

		void EnableKey(int key);
		void DisableKey(int key);

		static void GlfwMouseCallback(GLFWwindow* window, double xpos, double ypos)
		{
			Get().mouseCallback(window, xpos, ypos);
		}

		static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			Get().GlfwKeyCallbackDispatch(window, key, scancode, action, mods);
		}

		void mouseCallback(GLFWwindow* window, double xpos, double ypos);

		static void GlfwScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
		{
			Get().ScrollCallback(window, xoffset, yoffset);
		}

		void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

		void SetMouseLock(bool visible);
		glm::vec2 GetMousePostion();
		float GetMouseX();
		float GetMouseY();
		float GetScrollOffset();
		void Init(GLFWwindow* window);
		GLFWwindow* GetWindow() { return _Window; };

	private:
		InputManager() {}
		InputManager(InputManager const&) {};	//prevent copies
		void operator=(InputManager const&) {};	//prevent assignments

		struct keyBinding { int key; bool state; };

		//keyInputmap
		std::map<std::string, keyBinding> inputMap;
		//actionMap
		std::map<std::string, actionPTR> _ActionMap;
		
		std::list<std::string> _ActionList;

		GLFWwindow* _Window = nullptr;

		float scrollOffset;

		bool firstMouse = true;
		float lastX = 0.0f;
		float lastY = 0.0f;
};