#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <GameObject.h>
#include <map>

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

	//=========GAMEOBJECT===========START==
	//add and del gameobjects
	void AddGameObject(GameObject go);
	void DelGameObject(int id);
	//=========GAMEOBJECT=============END==


	//=========RIGIDBODY============START==
	//add and del rigidbodies
	void AddRigidBody(GameObject go);
	void DelRigidBody(int id);

	//modify rigidbodies
	void ModRigidBodyType(int id, int rbType);
	void ModRigidBodyGravity(int id, bool state);	// true == on

	//apply force to rigidbodies
	void ApplyRigidBodyForce(int id, Vector3 force);
	void ApplyRigidBodyForce(int id, Vector3 force, Vector3 point);
	void ApplyRigidBodyTorque(int id, Vector3 torque);

	//add and del rigidbody colliders
	void AddRigidBodyColliderBox(int id, Vector3 scale);
	void AddRigidBodyColliderSphere(int id, float radius);
	void AddRigidBodyColliderCapsule(int id, float radius, float height);
	//TODO add Model3D to convex function
	//TODO add Model3D to concave function
	void AddRigidBodyColliderHeightMap(int id, float* heightValues[], int nbRows, int nbCols, float minH, float maxH);
	
	//modify rigidbody colliders
	//TODO add collision filtering
	//TODO add trigger
	//MAYBE hinge and motor

	//=========RIGIDBODY==============END==

	//add and del collision bodies
	void AddColBody(GameObject go);
	void DelColBody(int id);

	//ray casting
	//TODO add Ray casting


	//simulation settings
	void SetTimeStep(float time);
	void StepPhysics();

	//update data storage
	void UpdateCbStore();
	void UpdateGoStore();

	//misc
	inline glm::vec3 react2glm(const Vector3& vec){return { vec.x, vec.y, vec.z };}

	std::map<int, GameObject> goStore;
private:
	//physics factory and world
	PhysicsCommon physicsCommon;	
	PhysicsWorld* world;

	//data storage
	std::map<int, RigidBody*> rbStore;
	std::map<int, Collider*> colStore;
	std::map<int, CollisionBody*> cbStore;


	//updates per second
	decimal timeStep = 0.0f;
	float accumulator = 0.0f;
	float previousFrameTime = 0.0f;
	float mDeltaTime = 0.0f;
};

