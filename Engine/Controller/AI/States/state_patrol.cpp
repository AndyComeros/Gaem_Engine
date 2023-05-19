#include "state_patrol.h"

State_Patrol::State_Patrol()
{
}

State_Patrol::State_Patrol(std::string& nTargetName)
{
}

State_Patrol::~State_Patrol()
{
}

void State_Patrol::Enter(GameObject& ent)
{
}

void State_Patrol::Update(GameObject& ent, double dt)
{
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;


}

void State_Patrol::Exit(GameObject& ent)
{
}

void State_Patrol::ProcessMessage(GameObject* ent, const Message* message)
{
}
