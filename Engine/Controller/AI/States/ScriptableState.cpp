#include "ScriptableState.h"

ScriptableState::ScriptableState(sol::function& nEnter, sol::function& nUpdate, sol::function& nExit){
	enterFunc = &nEnter;
	updateFunc = &nUpdate;
	exitFunc = &nExit;
}

ScriptableState::~ScriptableState()
{
}

void ScriptableState::Enter(GameObject& ent)
{
	try
	{
		(*enterFunc)(ent);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Scripted State Enter() failed: " << e.what() << std::endl;
	}
}

void ScriptableState::Update(GameObject& ent, double dt)
{
	try
	{
		(*updateFunc)(ent, dt);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Scripted State Update() failed: " << e.what() << std::endl;
	}
}

void ScriptableState::Exit(GameObject& ent)
{
	try
	{
		(*exitFunc)(ent);
	}
	catch (const std::exception& e)
	{
		std::cout << "ERROR: Scripted State Exit() failed: " << e.what() << std::endl;
	}
}


