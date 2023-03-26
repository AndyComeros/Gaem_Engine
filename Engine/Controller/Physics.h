#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <GameObject.h>
#include <map>

using namespace reactphysics3d;

class Physics
{
public:
	void CreatePhysicsWorld();
	void AddRigidBody();
	void AddRigidBody(GameObject go);

	void SetTimeStep(float time);
	void StepPhysics();
	void UpdateGO(GameObject go);
private:
	//physics factory and world
	PhysicsCommon physicsCommon;	
	PhysicsWorld* world;

	//rigidbody storage
	std::map<int, RigidBody*> rbStore;

	//updates per second
	decimal timeStep = 0.0f;
};
