#pragma once

//class used to manage the engine itself, run main loop, contains setup etc


class GameEngine
{
public:

	GameEngine();
	~GameEngine();

	//start main loop
	void Run();

private:
	double DeltaTime;
	double FPS;

};

