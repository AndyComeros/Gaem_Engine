#pragma once

#include <vector>
#include <map>

#include <GLFW/glfw3.h>

class InputManager
{
	public:
		//void AddInputInnerMap();

		void AddKey(int newKey);
		void RemoveKey(int keyToDel);

		void CheckInputLoop();

		void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		/*virtual void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void GlfwKeyCallBackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods){
			if (eventInstance)
				eventInstance->GlfwKeyCallback(window, key, scancode, action, mods);
		}
		virtual void setKeyCallbackEvent() { eventInstance = this; }
		static InputManager* eventInstance;*/

	private:
		//std::map<int, std::map<int, bool>> inputOuterMap;

		std::map<int, bool> inputMap;
};