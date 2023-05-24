#pragma once
#include <AI/Message/MessageDispatcher.h>
#include <lua/LuaManager.h>

class AIManager
{
public:
	static AIManager& Get();

	void UpdateAgents(double deltaTime);

	void Init(Scene* nScene);

	void AddState(const std::string& stateName, State*  nState);

	State* GetState(const std::string& stateName);

	std::string GetStateKey(State* state);
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
