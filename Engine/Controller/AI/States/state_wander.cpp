#include "state_wander.h"
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
	//ent.rigidBody.ApplyForce(glm::vec3(10, 0, 0));
	ent.SetPosition({ ent.position.x + (4 * dt), ent.position.y, ent.position.z});
}

inline void State_wander::Exit(GameObject& ent)
{

}

inline void State_wander::ProcessMessage(GameObject* ent, const Message* message)
{

}
