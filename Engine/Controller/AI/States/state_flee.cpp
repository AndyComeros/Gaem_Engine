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
	target = ResourceManager::Get().GetGameObject(targetName);

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	if (!npc->HasData("fleeSpeed"))
		npc->AddData("fleeSpeed", 20);

	if (!npc->HasData("fleeDistance"))
		npc->AddData("fleeDistance", 70);
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

	glm::vec3 toTarget = npc->position - target->position;

	if (toTarget.length() > npc->GetData("fleeDistance")) {
		//npc->stateMachine.
	}

}

void State_Flee::Exit(GameObject& ent)
{
}

void State_Flee::ProcessMessage(GameObject* ent, const Message* message)
{
}
