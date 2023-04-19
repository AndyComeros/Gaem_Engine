#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

// RigidBody type
#define KINE 1
#define STAT 2
#define DYNA 3

class Physics;
class GameObject;
class Terrain;

class Rigidbody
{
public:
	void ApplyForce(glm::vec3 force);
	void ApplyForceLocal(glm::vec3 force);
	void ApplyTorqueLocal(glm::vec3 torque);

	void ModType(int type);

	void SetUseGravity(bool isGravity);

	void SetPosition(glm::vec3 newPos);
	void SetRotation(glm::vec3 newRot);

	glm::vec3 GetPosition();

	void SetMass(float nMass);
	void SetCenterOfMass(glm::vec3 center);
	void SetDampeningLinear(float damp);
	void SetDampeningAngle(float damp);

	void SetAxisLinearFactor(float x, float y, float z);
	void SetAxisAngleFactor(float x, float y, float z);

	friend class Physics;
	friend class GameObject;
	friend class Terrain;
private:
	bool isContact = false;
	rp3d::RigidBody* rbPtr = nullptr;
	rp3d::PhysicsWorld* worldPtr = nullptr;
};