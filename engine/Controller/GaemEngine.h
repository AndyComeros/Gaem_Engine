#pragma once

#include <Renderer.h>
#include <GUIRenderer.h>
#include <InputManager.h>
#include <Physics.h>
#include <Lua/LuaManager.h>
/**
*	@Class GameEngine
*	@brief Used to manage the engine, windowing, controllers and run the main loop.
*	Setup as a singleton class for easy global access.
* 
*	@author Andres Comeros-Ochtman
*	@version 1.0
*	@date 15/04/2023
*/
class GameEngine
{
public:

		/**
		*	@brief Get the singleton instance of GameEngine
		*	@return The singleton instance of GameEngine
		*/
	static GameEngine& Get();

		/**
		*	@brief Runs the main game loop
		*	@return void
		*/
	void Run();

		/**
		*	@brief Calculates and returns time since last frame
		*	@return time since last frame
		*/
	double DeltaTime();
		/**
		*	@brief Calculates current FPS and returns value
		*	@return average Frame per second
		*/
	double GetFPS();
		/**
		*	@brief GLFW callback for window resizing. recalulates camera properties and viewport
		*	@param width new window width
		*	@param height new window height
		*	@return void
		*/
	static void ResizeCallback(GLFWwindow* window, int width, int height);		

		///Window width
	int wWidth = 1920;
		///Window height
	int wHeight = 1080;
		///Contains all data for rendering scene and stores world physics info
	Scene scene;
		///Window being drawn to and being used for inputs
	GLFWwindow* window;
		
		///Main Renderer
	Renderer renderer;
		///Main GUI Renderer
	GUIRenderer guirenderer;
		///Main Lua Manager
	LuaManager luaManager;
		///Reference to input manager
	InputManager& inputMngr = InputManager::Get();

private:
		///updates per second
	decimal timeStep = 0.0f;
		///time since last update
	double accumulator = 0.0f;
		///previous time between frames
	double previousFrameTime = 0.0f;
		///time since last frame
	double deltaTime = 0.0f;
		///whether main loop is running
	bool isRunning = false;
		//frames since last fps check
	int numFrames = 0;
		//current frame rate
	double fps = 0.0;
		//time since last fps update
	double lastTime = 0.0;
		
		///Default constructor. Private becuase singleton
	GameEngine();
		///Default Destructor.
	~GameEngine();
		///Assignment operator. Private becuase singleton
	GameEngine& operator =(const GameEngine&) = delete;
		///Copy constructor. Private becuase singleton
	GameEngine(const GameEngine&) = delete;
};