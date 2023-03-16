#pragma once

#include <vector>
#include <map>

#include <GLFW/glfw3.h>

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
		//void ToggleKey(int keyToTog);

		void KeyActions();

		static void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			getInstance().GlfwKeyCallbackDispatch(window, key, scancode, action, mods);
		}

		void GlfwKeyCallbackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods);

		/*virtual void GlfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void GlfwKeyCallBackDispatch(GLFWwindow* window, int key, int scancode, int action, int mods){
			if (eventInstance)
				eventInstance->GlfwKeyCallback(window, key, scancode, action, mods);
		}
		virtual void setKeyCallbackEvent() { eventInstance = this; }
		static InputManager* eventInstance;*/

	private:
		//std::map<int, std::map<int, bool>> inputOuterMap;
		InputManager(){}				
		InputManager(InputManager const&);		//prevent copies
		void operator=(InputManager const&);	//prevent assignments


		std::map<int, bool> inputMap;
		
};