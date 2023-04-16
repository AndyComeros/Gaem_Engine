#pragma once

#include <Renderer.h>
#include <GUIRenderer.h>
#include <InputManager.h>
#include <Physics.h>
#include <Lua/LuaManager.h>

//class used to manage the engine itself, run main loop, contains setup etc
//setup as a singleton. need only one and will be nice to have global access to deltatime, window size scene data etc.
class GameEngine
{
public:

	static GameEngine& Get();

	void Run();
	double DeltaTime();

	Scene scene;
	GLFWwindow* window;

	int wWidth = 500;
	int wHeight = 500;
	static void ResizeCallback(GLFWwindow* window, int width, int height);

	Renderer renderer;
	GUIRenderer guirenderer;
	LuaManager luaManager;
	InputManager& inputMngr = InputManager::Get();

private:
	//updates per second
	decimal timeStep = 0.0f;
	float accumulator = 0.0f;
	float previousFrameTime = 0.0f;
	float deltaTime = 0.0f;

	bool isRunning = false;

	GameEngine();
	~GameEngine();
	GameEngine& operator =(const GameEngine&) = delete;
	GameEngine(const GameEngine&) = delete;
};