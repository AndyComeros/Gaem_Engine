#pragma once

#include <Renderer.h>
//class used to manage the engine itself, run main loop, contains setup etc


class GameEngine
{
public:

	static GameEngine& Get();

	void Init();

	//start main loop
	void Run();

private:

	GLFWwindow* window;
	Renderer renderer;
	Scene* Scene;

	int wWidth = 500;
	int wHeight = 500;

	double deltaTime;
	double fps;


	GameEngine();
	~GameEngine();
	GameEngine(const GameEngine&);
	GameEngine& operator=(const GameEngine&);
};
