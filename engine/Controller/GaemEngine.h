#pragma once

#include <Renderer.h>
//class used to manage the engine itself, run main loop, contains setup etc


class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	//start main loop
	void Run();

private:
	double deltaTime;
	double fps;

	Renderer renderer;
};

