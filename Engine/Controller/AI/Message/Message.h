#pragma once

struct Message
{
	double dispatchTime;
	int senderID;
	int receiverID;
	int msgType;

	void* info;
	
	Message(double dispatch, int sender, int receiver, int type, void* infoPtr);

	//compare dispatch times
	bool operator< (const Message& m2)const;
	bool operator> (const Message& m2)const;
	bool operator==(const Message& m2)const;
};