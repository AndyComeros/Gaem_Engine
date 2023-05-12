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
	
	void AddData(std::string& dataName, float value);
	float GetData(std::string& dataName);
	bool HasData(std::string& dataName);
private:

	std::map<std::string, float> data;

};
