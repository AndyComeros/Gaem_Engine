#include "Input.h"

Input* Input::input_;

Input* Input::GetInstance()
{
	if (input_ == NULL)
	{
		input_ = new Input();

		return input_;
	}
	else
	{
		return input_;
	}
}

void Input::Forwards()
{
	float veloicty = _MoveSpeed * 0.033;
	_Player->position.z += veloicty;
	_Player->rotation.y = 90.0f;
}

void Input::Backwards()
{
	float veloicty = _MoveSpeed * 0.033;
	_Player->position.z -= veloicty;
	_Player->rotation.y = -90.0f;
}

void Input::Left()
{
	float veloicty = _MoveSpeed * 0.033;
	_Player->position.x += veloicty;
	_Player->rotation.y = 180;
}

void Input::Right()
{
	float veloicty = _MoveSpeed * 0.033;
	_Player->position.x -= veloicty;
	_Player->rotation.y = -0.0f;
}
