#include "StateMachine.h"
#include <iostream>
StateMachine::StateMachine(GameObject* nOwner) :
	owner(nOwner),
	currentState(nullptr),
	globalState(nullptr),
	previousState(nullptr)
{}

void StateMachine::ChangeState(State& nState)
{
	std::cout << "Chaning state!\n";
	if (previousState != &nState) {
		previousState = currentState;
		currentState = &nState;
		currentState->Enter(*owner);
	}
}

void StateMachine::ChangeGlobalState(State* nState)
{
	globalState = nState;
	globalState->Enter(*owner);
}

void StateMachine::RevertState()
{
	std::cout << "revert func!\n";
	if (previousState)
		ChangeState(*previousState);
}

void StateMachine::Update(double dt)
{
	if(currentState)
		currentState->Update(*owner, dt);
}

void StateMachine::ReceiveMessage(const Message* message)
{
	currentState->ProcessMessage(owner, message);
	globalState->ProcessMessage(owner, message);
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
