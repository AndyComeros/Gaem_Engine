#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// RigidBody type
#define KINE 1
#define STAT 2
#define DYNA 3

class Physics;

class Rigidbody
{
public:
	void ApplyForce(glm::vec3 force);
	void ApplyTorque(glm::vec3 torque);

	void ModType(int type);

	void SetUseGravity(bool isGravity);

	void SetPosition(glm::vec3 newPos);
	glm::vec3 GetPosition();


	friend class Physics;
private:
	rp3d::RigidBody* rbPtr = nullptr;
};

