#include "AIManager.h"

AIManager& AIManager::Get()
{
	static AIManager a_instance;
	return a_instance;
}

void AIManager::UpdateAgents(double deltaTime)
{
	if (!scene) {
		return;
	}

	msgDispatcher->SendMsgQueue();
	for (auto& it: scene->gameObjects)
	{
		if (it.second) {
			it.second->Update(deltaTime);
			it.second->stateMachine.Update(deltaTime);
		}
	}
}

void AIManager::Init(Scene* nScene)
{
	scene = nScene;
	msgDispatcher->SetScene(nScene);
}

void AIManager::AddState(const std::string& stateName, State* nState)
{
	states.insert({stateName,nState});
	LuaManager::Get().Expose_CPPReference(stateName.c_str(), *nState);
}

State* AIManager::GetState(const std::string& stateName)
{
	State* rState = states[stateName];

	if (rState != nullptr)
		return rState;

	return nullptr;
}

std::string AIManager::GetStateKey(State* state)
{
	for (auto& it : states) {
		if (state == it.second)
			return it.first;
	}
	return "";
}

AIManager::AIManager()
{
	msgDispatcher = &Dispatcher::Get();
}

AIManager::~AIManager()
{
}
