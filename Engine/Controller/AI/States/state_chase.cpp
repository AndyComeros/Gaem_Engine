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

	npc->GetDrawItem().Animate("run");
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

	npc->LookAt(target->position);
	npc->MoveTo3D(target->position,npc->GetData("speed"), npc->GetData("offset"));

	float nY = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(npc->position.x, npc->position.z) - 1;
	npc->SetPosition({ npc->position.x,nY,npc->position.z });
	
}

void State_Chase::Exit(GameObject& ent)
{
}

void State_Chase::ProcessMessage(GameObject* ent, const Message* message)
{
}
