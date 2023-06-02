#pragma once
#include <AI/Message/MessageDispatcher.h>

class AIManager
{
public:
	static AIManager& Get();

	void UpdateAgents(double deltaTime);

	void Init(Scene* nScene);

	void AddState(const std::string& stateName, State*  nState);

	State* GetState(const std::string& stateName);

	void SendMessage(double delay, int sender, int receiver, int type);

	std::string GetStateKey(State* state);
private:

	Dispatcher* msgDispatcher;
	Scene* scene;
	std::map<std::string, State*> states;

	double accumilator = 0;
	double updateTime = 0;

	//singleton
	AIManager();
	~AIManager();
	AIManager(const AIManager&) = delete;
	AIManager& operator = (const AIManager&) = delete;
};
