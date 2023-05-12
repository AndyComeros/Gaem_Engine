#pragma once
#include <set>
#include "Message.h"
#include <GaemEngine.h>
#include <AI/StateMachine.h>


class Dispatcher
{
public:
	
	Dispatcher& Get();
	void SendMessage(double delay, int sender, int receiver, int type, void* data);
		//checks if message queue items can be sent yet.
	void SendMsgQueue();

private:
	//messages with delays
	std::set<Message> msgQueue;
	
	Scene* scene;

	//singleton
	Dispatcher();
	~Dispatcher();
	Dispatcher(const Dispatcher&) = delete;
	Dispatcher& operator = (const Dispatcher&) = delete;
};