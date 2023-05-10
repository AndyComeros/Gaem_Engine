#pragma once

class GameObject;
class State
{
public:
	virtual ~State() {};

	virtual void Enter(GameObject& ent) = 0;
	virtual void Update(GameObject& ent, double dt) = 0;
	virtual void Exit(GameObject& ent) = 0;

private:

};