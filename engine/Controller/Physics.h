#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <GameObject.h>
//#include <map>

using namespace reactphysics3d;

// RigidBody type
#define KINE 1
#define STAT 2
#define DYNA 3

class Physics
{
public:
	void CreatePhysicsWorld();
	void DestroyPhysicsWorld();

	//=========RIGIDBODY============START==
	//add and del rigidbodies
	void AddRigidBody(GameObject &go);
	void DelRigidBody(GameObject &go);

	//modify rigidbodies
	void ModRigidBodyType(GameObject &go, int rbType);
	void ModRigidBodyGravity(GameObject &go, bool state);	// true == on

	//apply force to rigidbodies
	void ApplyRigidBodyForce(GameObject &go, Vector3 force);
	void ApplyRigidBodyForce(GameObject &go, Vector3 force, Vector3 point);
	void ApplyRigidBodyTorque(GameObject &go, Vector3 torque);

	//add and del rigidbody colliders
	void AddRigidBodyColliderBox(GameObject &go, Vector3 scale);
	void AddRigidBodyColliderSphere(GameObject &go, float radius);
	void AddRigidBodyColliderCapsule(GameObject &go, float radius, float height);
	//TODO add Model3D to convex function
	//TODO add Model3D to concave function
	void AddRigidBodyColliderHeightMap(GameObject &go, unsigned char* heightValues, int nbRows, int nbCols, float minH, float maxH);
	
	//modify rigidbody colliders
	//TODO add collision filtering
	//TODO add trigger
	//MAYBE hinge and motor

	//=========RIGIDBODY==============END==


	//ray casting
	//TODO add Ray casting

	//update GO vector
	void updateGameObjects(std::vector<GameObject>& goStore);


	//simulation settings
	void SetTimeStep(float time);
	void StepPhysics();					

	//misc
	inline glm::vec3 react2glm(const Vector3& vec){return { vec.x, vec.y, vec.z };}
	void ToggleDebugDisplay() { DispDebug = !DispDebug; }
private:
	//physics factory and world
	PhysicsCommon physicsCommon;	
	PhysicsWorld* world;

	//updates per second
	decimal timeStep = 0.0f;
	float accumulator = 0.0f;
	float previousFrameTime = 0.0f;
	float mDeltaTime = 0.0f;
	bool DispDebug = false;

	//display debug 
	void DebugDisplay();
};

