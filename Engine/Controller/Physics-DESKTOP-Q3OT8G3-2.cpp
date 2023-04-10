#include "physics.h"

void Physics::SetupPhysWorld()
{
	// Build the broadphase
	btBroadphaseInterface* broadphase = new btDbvtBroadphase();

	// Set up the collision configuration and dispatcher
	btDefaultCollisionConfiguration* collisionConfiguration = new btDefaultCollisionConfiguration();
	btCollisionDispatcher* dispatcher = new btCollisionDispatcher(collisionConfiguration);

	// The actual physics solver
	btSequentialImpulseConstraintSolver* solver = new btSequentialImpulseConstraintSolver;

	//world
	worldPhys = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	//set gravity
	worldPhys->setGravity(btVector3(0, -9.81f, 0));
}

void Physics::AddRigidBody(GameObject go)
{
	btCollisionShape* boxCollisionShape = new btBoxShape(btVector3(1.0f, 1.0f, 1.0f));

	btDefaultMotionState* motionstate = new btDefaultMotionState(btTransform(
		btQuaternion(go.rotation.x, go.rotation.y, go.rotation.z, 1),						////TEST////
		btVector3(go.position.x, go.position.y, go.position.z)
	));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
		0,                  // mass, in kg. 0 -> Static object, will never move.
		motionstate,
		boxCollisionShape,  // collision shape of body
		btVector3(0, 0, 0)    // local inertia
	);
	btRigidBody* rigidBody = new btRigidBody(rigidBodyCI);

	worldPhys->addRigidBody(rigidBody);
}
