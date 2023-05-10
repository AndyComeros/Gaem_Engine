#include "StateMachine.h"

StateMachine::StateMachine(GameObject* nOwner) :
	owner(nOwner),
	currentState(nullptr),
	globalState(nullptr),
	previousState(nullptr)
{}

void StateMachine::ChangeState(State* nState)
{
	currentState = nState;
	if(previousState != currentState)
		currentState->Enter(*owner);
}

void StateMachine::ChangeGlobalState(State* nState)
{
	globalState = nState;
	globalState->Enter(*owner);
}

void StateMachine::RevertState()
{
	if (previousState)
		ChangeState(previousState);
}

void StateMachine::Update(double dt)
{
	if(currentState)
		currentState->Update(*owner, dt);
}

State* StateMachine::GetState()
{
	return currentState;
}

State* StateMachine::GetGlobalState()
{
	return globalState;
}

State* StateMachine::GetPreviousState()
{
	return previousState;
}
