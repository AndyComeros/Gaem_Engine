#pragma once
#include "State.h"
#include <Lua/LuaManager.h>

class ScriptableState : public State
{
public:
	ScriptableState(sol::function& nEnter, sol::function& nUpdate, sol::function& nExit);
	~ScriptableState();

	void Enter(GameObject& ent);
	void Update(GameObject& ent, double dt);
	void Exit(GameObject& ent);
private:

	sol::function* enterFunc;
	sol::function* updateFunc;
	sol::function* exitFunc;

};