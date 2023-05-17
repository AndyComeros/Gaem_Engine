#include "state_wander.h"

State_wander::State_wander()
{

}

State_wander::~State_wander()
{

}

inline void State_wander::Enter(GameObject& ent)
{
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	if (!npc->HasData("wanderRadius")) 
		npc->AddData("wanderRadius", 20);
	
	if (!npc->HasData("wanderDistance")) 
		npc->AddData("wanderDistance", 20);

	if (!npc->HasData("wanderJitter"))
		npc->AddData("wanderJitter", 20);

	if (!npc->HasData("tarX"))
		npc->AddData("tarX", 0);
	if (!npc->HasData("tarY"))
		npc->AddData("tarY", 0);
	if (!npc->HasData("tarZ"))
		npc->AddData("tarZ", 0);

}

inline void State_wander::Update(GameObject& ent, double dt)
{	
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	double moveSpeed = dt * npc->GetData("wanderJitter");

	ent.SetPosition({ ent.position.x + (npc->GetData("wanderRadius") * dt), ent.position.y, ent.position.z});
}

inline void State_wander::Exit(GameObject& ent)
{

}

inline void State_wander::ProcessMessage(GameObject* ent, const Message* message)
{

}
