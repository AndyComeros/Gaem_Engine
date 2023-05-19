#pragma once
#include "State.h"
#include <ResourceManager.h>
#include <AI/AIManager.h>

class State_Patrol : public State
{
public:
	State_Patrol();
	State_Patrol(std::string& nTargetName);
	~State_Patrol();

	void Enter(GameObject& ent);
	void Update(GameObject& ent, double dt);
	void Exit(GameObject& ent);
	void ProcessMessage(GameObject* ent, const Message* message);

private:
};