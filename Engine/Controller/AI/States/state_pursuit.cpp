#include "state_pursuit.h"

State_Pursuit::State_Pursuit()
{
	targetName = "Player";
	target = nullptr;
}

State_Pursuit::State_Pursuit(std::string& nTargetName)
{
	target = nullptr;
	targetName = nTargetName;
}

State_Pursuit::~State_Pursuit()
{
}

void State_Pursuit::Enter(GameObject& ent)
{
	target = ResourceManager::Get().GetGameObject(targetName);

	NPC* npc = dynamic_cast<NPC*>(&ent);
	if (npc == nullptr)
		return;

	if (!npc->HasData("speed"))
		npc->AddData("speed", 20);

	if (!npc->HasData("offset"))
		npc->AddData("offset", 5);
}

void State_Pursuit::Update(GameObject& ent, double dt)
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

	if (glm::dot(target->GetForwardVec(), toTarget) < -0.95f) {
		npc->MoveTo(target->position, npc->GetData("speed"), npc->GetData("offset"));
	}
	else {
		glm::vec3 targetVel = target->rigidBody.GetLinearVelocty();

		npc->MoveTo(target->position + targetVel * 2.0f, npc->GetData("speed"), npc->GetData("offset"));
	}

	//lock to terrain height
	float nY = static_cast<Terrain*>(ResourceManager::Get().GetGameObject("Terrain"))->GetHeight(npc->position.x, npc->position.z) + 1.0f;
	npc->SetPosition({ npc->position.x,nY,npc->position.z });

}

void State_Pursuit::Exit(GameObject& ent)
{
}

void State_Pursuit::ProcessMessage(GameObject* ent, const Message* message)
{
}
