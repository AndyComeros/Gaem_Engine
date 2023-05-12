#pragma once
#include <AI/Message/MessageDispatcher.h>

class AIManager
{
public:
	static AIManager& Get();

	void UpdateAgents(double deltaTime);

	void Init(Scene* nScene);
private:

	Dispatcher* msgDispatcher;
	Scene* scene;

	//singleton
	AIManager();
	~AIManager();
	AIManager(const AIManager&) = delete;
	AIManager& operator = (const AIManager&) = delete;
};
