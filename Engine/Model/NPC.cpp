#include "NPC.h"

NPC::NPC() : 
targetPos({ 0.0f,0.0f,0.0f }),
moveSpeed(0.0f),
moveOffset(0.0f),
isTargeting(false)
{
}

NPC::~NPC()
{
}

void NPC::AddData(const std::string& dataName, float value)
{
	data[dataName] = value;
	//data.insert({ dataName, value });
}



float NPC::GetData(const std::string& dataName)
{
	if (data.find(dataName) != data.end()) {
		return data.at(dataName);
	}
	else {
		return 0.0f;
	}
}

bool NPC::HasData(const std::string& dataName)
{
	if (data.find(dataName) != data.end()) {
		return true;
	}
	else {
		return false;
	}
}

void NPC::Update(double dt)
{
	if (!isTargeting)
		return;

	glm::vec3 toTarget = targetPos - position;
	toTarget = glm::normalize(toTarget);
	glm::vec3 newPos = position + (toTarget) * (float)(moveSpeed * dt);

	//check if overshooting target
	glm::vec3 offsetPos = targetPos - toTarget * moveOffset;
	glm::vec3 toOffset = offsetPos - newPos;
	if (glm::dot(toOffset, toTarget) < 0.0f) {
		newPos = offsetPos;
		isTargeting = false;
	}

	position = newPos;
}

void NPC::MoveTo(glm::vec3 nPos, float speed, float offset)
{
	isTargeting = true;
	targetPos = nPos;
	moveSpeed = speed;
	moveOffset = offset;
}

void NPC::StopMoving()
{
	isTargeting = false;
}
