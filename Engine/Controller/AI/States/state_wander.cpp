#include "state_wander.h"
#include <iostream>
State_wander::State_wander()
{

}

State_wander::~State_wander()
{

}

inline void State_wander::Enter(GameObject& ent)
{

}

inline void State_wander::Update(GameObject& ent, double dt)
{	
	std::cout << ent.name << " says ima wanderin!\n";
}

inline void State_wander::Exit(GameObject& ent)
{

}

inline void State_wander::ProcessMessage(GameObject* ent, const Message* message)
{

}
