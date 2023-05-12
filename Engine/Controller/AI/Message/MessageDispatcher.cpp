#include "MessageDispatcher.h"

Dispatcher& Dispatcher::Get()
{
	static Dispatcher d_instance;
	return d_instance;
}

void Dispatcher::SendMessage(double delay, int sender, int receiver, int type, void* data)
{
	GameObject* nReceiver = scene->GetObjectByID(receiver);
	//GameObject* nSender = scene->GetObjectByID(sender);

	if (nReceiver) {
		std::cerr << "Could not send message!" << std::endl;
		return;
	}

}

void Dispatcher::SendMsgQueue()
{

}

Dispatcher::Dispatcher()
{
	scene = &GameEngine::Get().scene;
}

Dispatcher::~Dispatcher()
{

}
