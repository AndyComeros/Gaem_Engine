#pragma once
#include "State.h"
#include <ResourceManager.h>

class State_wander : public State 
{
public:
	State_wander();
	~State_wander();

	void Enter(GameObject& ent);
	void Update(GameObject& ent, double dt);
	void Exit(GameObject& ent);
	void ProcessMessage(GameObject* ent, const Message* message);


private:

};