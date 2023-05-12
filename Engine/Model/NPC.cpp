#include "NPC.h"

NPC::NPC()
{
}

NPC::~NPC()
{
}

void NPC::AddData(std::string& dataName, float value)
{
	data.insert({ dataName, value });
}

float NPC::GetData(std::string& dataName)
{
	return data.at(dataName);
}

bool NPC::HasData(std::string& dataName)
{
	if (data.find(dataName) != data.end()) {
		return true;
	}
	else {
		return false;
	}
}
