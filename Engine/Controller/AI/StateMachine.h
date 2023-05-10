#pragma once
#include "State.h"

template<class entity_type>
class StateMachine
{
public:
	StateMachine();
	~StateMachine();
	void ChangeState(State* nState);
	void PreviousState();
	void Update();

private:
	entity_type* owner;
	State* currentState;
	State* globalState;
	State* previousState;


};