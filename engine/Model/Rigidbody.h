#pragma once
#include <Physics.h>

class Rigidbody
{
public:

	friend class Physics;
private:
	Rigidbody* rbPtr = nullptr;
};

