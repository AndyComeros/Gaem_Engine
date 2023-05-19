#pragma once
#include <AI/Message/MessageDispatcher.h>

class AIManager
{
public:
	static AIManager& Get();

	void UpdateAgents(double deltaTime);

	void Init(Scene* nScene);

	void AddState(std::string& stateName, State*  nState);

	State* GetState(std::string& stateName);
private:

	Dispatcher* msgDispatcher;
	Scene* scene;
	std::map<std::string, State*> states;

	//singleton
	AIManager();
	~AIManager();
	AIManager(const AIManager&) = delete;
	AIManager& operator = (const AIManager&) = delete;
};
