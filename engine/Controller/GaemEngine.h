#pragma once

#include <Renderer.h>

//class used to manage the engine itself, run main loop, contains setup etc
//setup as a singleton. need only one and will be nice to have global access to deltatime, window size scene data etc.
class GameEngine
{
public:

	static GameEngine& Get();

	void Run();

	Scene scene;
	GLFWwindow* window;
	Renderer renderer;

	int wWidth = 500;
	int wHeight = 500;

private:

	double deltaTime;
	double fps;

	bool isRunning = false;
	
	GameEngine();
	~GameEngine();
	GameEngine(const GameEngine&);
	GameEngine& operator=(const GameEngine&) {};
};