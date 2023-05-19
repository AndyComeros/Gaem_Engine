#pragma once
#include "State.h"
#include <ResourceManager.h>

class State_Flee : public State
{
public:
	State_Flee();
	State_Flee(std::string&);
	~State_Flee();

	void Enter(GameObject& ent);
	void Update(GameObject& ent, double dt);
	void Exit(GameObject& ent);
	void ProcessMessage(GameObject* ent, const Message* message);

private:
	GameObject* target;
	std::string targetName;
};