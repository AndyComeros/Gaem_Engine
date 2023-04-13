#pragma once

#include <Renderer.h>
#include <InputManager.h>
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

	Renderer renderer;
	LuaManager luaManager;

	InputManager& inputMngr = InputManager::getInstance();
	
	int wWidth = 500;
	int wHeight = 500;
	static void ResizeCallback(GLFWwindow* window, int width, int height);

	float lastX = 250, lastY = 250;
private:

	double deltaTime;
	double prevTime;
	double fps;

	bool isRunning = false;

	GameEngine();
	~GameEngine();
	GameEngine& operator =(const GameEngine&) = delete;
	GameEngine(const GameEngine&) = delete;
};