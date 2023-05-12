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
			it.second->stateMacine.Update(deltaTime);
		}
	}
}

void AIManager::Init(Scene* nScene)
{
	scene = nScene;
	msgDispatcher->SetScene(nScene);
}

AIManager::AIManager()
{
	msgDispatcher = &Dispatcher::Get();
}

AIManager::~AIManager()
{
}
