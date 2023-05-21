#pragma once
#include <set>
#include <Scene.h>
#include <Timer.h>
#include <AI/StateMachine.h>


class Dispatcher
{
public:
	
	static Dispatcher& Get();
	void SendMessage(double delay, int sender, int receiver, int type, void* data);
		//checks if message queue items can be sent yet.
	void SendMsgQueue();

	void SetScene(Scene* nScene);

private:
	//messages with delays
	std::set<Message> msgQueue;
	Scene* scene = nullptr;

	//singleton
	Dispatcher();
	~Dispatcher();
	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator = (const Dispatcher&) = delete;
};