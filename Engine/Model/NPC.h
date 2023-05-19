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

	void AddPointer(const std::string& dataName, void* ptr);
	bool HasPointer(const std::string& dataName);

	template<typename T>
	T* GetPointer(const std::string& dataName) {

		if (pointers.find(dataName) != pointers.end()) {
			return pointers.at(dataName);
		}
		else {
			return nullptr;
		}
	}

	void Update(double dt);

	//npc will move to position at speed
	//offset is how close to get to target before stopping
	void MoveTo(glm::vec3 nPos, float speed, float offset);
	void StopMoving();

private:

	glm::vec3 targetPos;
	float moveSpeed;
	//how close to stop in front of target
	float moveOffset;
	bool isTargeting;

		//stores values
	std::map<std::string, float> data;

		//stores arbitrary data
	std::map<std::string, void*> pointers;

};
