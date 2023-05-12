#include "MessageDispatcher.h"

Dispatcher& Dispatcher::Get()
{
	static Dispatcher d_instance;
	return d_instance;
}

void Dispatcher::SendMessage(double delay, int sender, int receiver, int type, void* data)
{
	GameObject* nReceiver = scene->GetObjectByID(receiver);

	if (nReceiver) {
		std::cerr << "Could not send message!" << std::endl;
		return;
	}

	Message message(0.0,sender,receiver,type,data);

	if (delay < 0.1) {
		nReceiver->stateMacine.ReceiveMessage(&message);
	}
	else {
		message.dispatchTime = delay + GameEngine::Get().Time();
		msgQueue.insert(message);
	}
}

void Dispatcher::SendMsgQueue()
{
	double time = GameEngine::Get().Time();
	while (!msgQueue.empty() && msgQueue.begin()->dispatchTime < time)
	{
		GameObject* rec = scene->GetObjectByID(msgQueue.begin()->receiverID);
		if(rec)
			rec->stateMacine.ReceiveMessage(&*msgQueue.begin());
		msgQueue.erase(msgQueue.begin());
	}
}

Dispatcher::Dispatcher()
{
	scene = &GameEngine::Get().scene;
}

Dispatcher::~Dispatcher()
{

}
