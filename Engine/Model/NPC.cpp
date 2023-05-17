#include "NPC.h"

NPC::NPC()
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
