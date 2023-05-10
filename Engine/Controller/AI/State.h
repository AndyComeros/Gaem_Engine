#pragma once

class StateMachine;
class State
{
public:
	State() {};
	~State() {};

	void Enter(StateMachine& ent) = 0;
	void Update(StateMachine& ent) = 0;
	void Exit(StateMachine& ent) = 0;

private:

};