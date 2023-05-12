#pragma once
#include <LUA/LuaManager.h>
#include "state_wander.h"


State_wander state_wander;


void ExposeStates() {
	LuaManager& manager = LuaManager::Get();

	manager.Expose_CPPVariable("state_wander", state_wander);
}
