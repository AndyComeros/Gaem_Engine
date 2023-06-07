#pragma once
#include <GameObject.h>
#include <map>
#include <string>

//subclass of game object, stores npc data.
class NPC : public GameObject
{
public:
	NPC();
	~NPC();
	
	void AddData(const std::string& dataName, float value);
	bool HasData(const std::string& dataName);
	float GetData(const std::string& dataName);
	void Update(double dt);

	//npc will move to position at speed
	//offset is how close to get to target before stopping
	void MoveTo3D(glm::vec3 nPos, float speed, float offset);
	void MoveTo2D(glm::vec3 nPos, float speed, float offset);
	void StopMoving();
	bool IsTargeting();


	//stores arbitrary values
	std::map<std::string, float> data;
private:

	glm::vec3 targetPos;
	float moveSpeed;
	//how close to stop in front of target
	float moveOffset;
	bool isTargeting;
	bool move3D;

	//movement variables
	glm::vec3 offsetPos;
	glm::vec3 toOffset;
	glm::vec3 newPos;
	glm::vec3 toTarget;
};
