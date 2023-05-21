#include "state_wander.h"

State_Wander::State_Wander()
{
	target = { 0,0,0 };
}

State_Wander::~State_Wander()
{

}

inline void State_Wander::Enter(GameObject& ent)
{
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;
	
	npc->AddData("wanderDistance", 20.0f);
	npc->AddData("wanderSpeed", 20.0f);

	npc->AddData("maxWander", 10.0f);
	npc->AddData("maxIdle", 10.0f);

	npc->AddData("wanderTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxWander"))));
	npc->AddData("idleTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxIdle"))));

	npc->AddData("isIdle", 0.0f);
	npc->AddData("timer", 0.0f);

	npc->StopMoving();
	PickWanderTarget();
}

inline void State_Wander::Update(GameObject& ent, double dt)
{	
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	float moveSpeed = dt * npc->GetData("wanderSpeed");
	
	//if not idle
	if (npc->GetData("isIdle") < 0.5f) {

		//lock to terrain height
		float nY = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(npc->position.x, npc->position.z) + 1.0f;
		npc->SetPosition({ npc->position.x,nY,npc->position.z });

		npc->LookAt(target);

		//if been walking too long
		if (npc->GetData("timer") > npc->GetData("wanderTime")) {
			npc->AddData("isIdle", 1.0f);
			npc->AddData("timer", 0.0f);
			npc->AddData("wanderTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxWander"))));
			npc->StopMoving();
		}
	}
	else {

		npc->GetDrawItem().Animate("stand");

		//if idling too long
		if (npc->GetData("timer") > npc->GetData("idleTime")) {
			npc->AddData("isIdle", 0.0f);
			npc->AddData("timer", 0.0f);
			npc->AddData("idleTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxIdle"))));

			//pick new target location
			npc->GetDrawItem().Animate("run");
			PickWanderTarget();
			npc->MoveTo2D(target,npc->GetData("wanderSpeed"),0);
		}
	}

	//increment timer
	npc->AddData("timer", npc->GetData("timer") + dt);

}

inline void State_Wander::Exit(GameObject& ent)
{
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	npc->AddData("timer", 0.0f);
	npc->AddData("wanderTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxWander"))));
	npc->AddData("idleTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxIdle"))));
}

inline void State_Wander::ProcessMessage(GameObject* ent, const Message* message)
{

}

void State_Wander::PickWanderTarget()
{
	float sx = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetScaleX();
	float sz = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetScaleZ();

	float nx = -sx/2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sx));
	float nz = -sz/2 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / sz));
	float ny = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(nx, nz) + 1;
	target = { nx,ny,nz };
}
