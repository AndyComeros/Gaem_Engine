#pragma once

#include <Renderer.h>

//class used to manage the engine itself, run main loop, contains setup etc

class GameEngine
{
public:

	static GameEngine& Get();

	void Run();

	Scene scene;
	GLFWwindow* window;
	Renderer renderer;
	

private:

	int wWidth = 500;
	int wHeight = 500;

	double deltaTime;
	double fps;

	bool isRunning = false;
	

	GameEngine();
	~GameEngine();
	GameEngine(const GameEngine&);
	GameEngine& operator=(const GameEngine&);
};