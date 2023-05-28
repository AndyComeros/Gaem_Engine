#include "state_flee.h"

State_Flee::State_Flee()
{
	targetName = "Player";
	target = nullptr;
}

State_Flee::State_Flee(std::string& nTarget)
{
	targetName = nTarget;
	target = nullptr;
}

State_Flee::~State_Flee()
{
}

void State_Flee::Enter(GameObject& ent)
{
	if(!target)
		target = ResourceManager::Get().GetGameObject(targetName);
	if (!stateWander)
		stateWander = AIManager::Get().GetState("state_wander");

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	if (!npc->HasData("fleeSpeed"))
		npc->AddData("fleeSpeed", 20);

	if (!npc->HasData("fleeDistance"))
		npc->AddData("fleeDistance", 300);

	npc->GetDrawItem().Animate("run");
}

void State_Flee::Update(GameObject& ent, double dt)
{
	if (!target) {
		target = ResourceManager::Get().GetGameObject(targetName);
		if (!target)
			return;
	}

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	glm::vec3 toTarget = target->position - npc->position;

	glm::vec3 nPos = npc->position - glm::normalize(toTarget);
	npc->LookAt(nPos);
	npc->MoveTo3D(nPos, npc->GetData("fleeSpeed"), 0);

	//lock to terrain height
	float nY = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(npc->position.x, npc->position.z) - 1;
	npc->SetPosition({ npc->position.x,nY,npc->position.z });
	
	if (fabs(glm::length(toTarget)) > npc->GetData("fleeDistance")) {
		npc->stateMachine.ChangeState(*stateWander);
	}

}

void State_Flee::Exit(GameObject& ent)
{
	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	npc->StopMoving();
}

void State_Flee::ProcessMessage(GameObject* ent, const Message* message)
{
}
