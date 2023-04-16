#pragma once
#include <GameObject.h>
class Input
{
protected:
	static Input* input_;
public:
	static Input* GetInstance();

	static void forwards() { input_->Forwards(); };
	static void backwards() { input_->Backwards(); };
	static void left() { input_->Left(); };
	static void right() { input_->Right(); };

	void setPlayer(GameObject &player) { _Player = &player; };
private:
	void Forwards();
	void Backwards();
	void Left();
	void Right();

	Input() {};
	Input(Input const&) {};

	float _MoveSpeed = 20;
	GameObject* _Player = new GameObject();
	Camera* _Camera;

	bool firstPerson;
};

