#include "state_chase.h"

State_Chase::State_Chase()
{
	targetName = "Player";
	target = nullptr;
}

State_Chase::State_Chase(std::string& nTargetName)
{
	target = nullptr;
	targetName = nTargetName;
}

State_Chase::~State_Chase()
{
}

void State_Chase::Enter(GameObject& ent)
{
	target = ResourceManager::Get().GetGameObject(targetName);

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	if(!npc->HasData("speed"))
		npc->AddData("speed", 20);

	if (!npc->HasData("offset"))
		npc->AddData("offset", 5);
}

void State_Chase::Update(GameObject& ent, double dt)
{
	if (!target) {
		target = ResourceManager::Get().GetGameObject(targetName);
		if (!target)
			return;
	}

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	npc->MoveTo(target->position,npc->GetData("speed"), npc->GetData("offset"));
}

void State_Chase::Exit(GameObject& ent)
{
}

void State_Chase::ProcessMessage(GameObject* ent, const Message* message)
{
}
