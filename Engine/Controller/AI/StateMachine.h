#pragma once
#include "States/State.h"

class GameObject;

class StateMachine
{
public:
	StateMachine(GameObject* nOwner);

	~StateMachine() {}
	void ChangeState(State& nState);
	void ChangeGlobalState(State* nState);
	void RevertState();

	void Update(double dt);

	void ReceiveMessage(const Message* message);

	State* GetState();
	State* GetGlobalState();
	State* GetPreviousState();

private:
	GameObject* owner;
	State* currentState;
	State* globalState;
	State* previousState;
};