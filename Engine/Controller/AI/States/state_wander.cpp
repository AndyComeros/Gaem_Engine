#include "state_wander.h"

State_Wander::State_Wander()
{

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

}

inline void State_Wander::Update(GameObject& ent, double dt)
{	
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	float moveSpeed = dt * npc->GetData("wanderSpeed");
	
	//if not idle
	if (npc->GetData("isIdle") < 0.5f) {
		//move forward

		glm::vec3 npos = npc->position + (npc->GetForwardVec() * moveSpeed);
		npos.y = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(npos.x,npos.z) + 1.0f;
		npc->SetPosition(npos);

		//if been walking too long
		if (npc->GetData("timer") > npc->GetData("wanderTime")) {
			npc->AddData("isIdle", 1.0f);
			npc->AddData("timer", 0.0f);
			npc->AddData("wanderTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxWander"))));
		}
	}
	else {

		//if idling too long
		if (npc->GetData("timer") > npc->GetData("idleTime")) {
			npc->AddData("isIdle", 0.0f);
			npc->AddData("timer", 0.0f);
			npc->AddData("idleTime", (static_cast<float>(rand()) / static_cast<float>(RAND_MAX / npc->GetData("maxIdle"))));

			//pick new direction
			glm::vec3 rot = npc->rotation;
			rot.y += -360.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f - (-360.0f))));
			npc->SetRotation(rot);
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
