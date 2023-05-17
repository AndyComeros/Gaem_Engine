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
	float GetData(const std::string& dataName);
	bool HasData(const std::string& dataName);
private:

	std::map<std::string, float> data;

};
