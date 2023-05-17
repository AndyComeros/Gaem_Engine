#include "state_wander.h"
#include <random>

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
	
	npc->AddData("wanderDistance", 20.0f);
	npc->AddData("wanderSpeed", 20.0f);

	npc->AddData("wanderTime", 5.0f);
	npc->AddData("maxWander", 10.0f);
	npc->AddData("idleTime", 5.0f);
	npc->AddData("maxIdle", 10.0f);
	npc->AddData("isIdle", 0.0f);
	npc->AddData("timer", 0.0f);

	npc->AddData("tarX", 0.0f);
	npc->AddData("tarY", 0.0f);
	npc->AddData("tarZ", 0.0f);

}

inline void State_wander::Update(GameObject& ent, double dt)
{	
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	float moveSpeed = dt * npc->GetData("wanderSpeed");
	
	//if not idle
	if (npc->GetData("isIdle") < 0.5f) {
		//move forward
		npc->SetPosition(npc->position + (npc->GetForwardVec() * moveSpeed));

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

			glm::vec3 rot = npc->rotation;
			rot.y += -360.0f + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (360.0f - (-360.0f))));
			npc->SetRotation(rot);

		}
	}

	//increment timer
	//std::cout << "time: " << npc->GetData("timer") << "\n";
	npc->AddData("timer", npc->GetData("timer") + dt);

}

inline void State_wander::Exit(GameObject& ent)
{

}

inline void State_wander::ProcessMessage(GameObject* ent, const Message* message)
{

}
