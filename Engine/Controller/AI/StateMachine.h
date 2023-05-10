#pragma once
#include "State.h"

template<class entity_type>
class StateMachine
{
public:
	StateMachine(entity_type* nOwner):
	owner(nOwner),
	currentState(nullptr),
	globalState(nullptr),
	previousState(nullptr)
	{}
	~StateMachine() {}
	void ChangeState(State<entity_type>* nState);
	void ChangeGlobalState(State<entity_type>* nState);
	void RevertState();

	void Update();

	

	State<entity_type>* GetState();
	State<entity_type>* GetGlobalState();
	State<entity_type>* GetPreviousState();

private:
	entity_type* owner;
	State<entity_type>* currentState;
	State<entity_type>* globalState;
	State<entity_type>* previousState;
};