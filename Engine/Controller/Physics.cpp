#include <Physics.h>

void Physics::CreatePhysicsWorld()
{
	world = physicsCommon.createPhysicsWorld();
}

void Physics::AddRigidBody()
{
	Vector3 position(0, 20, 0);
	Quaternion orientation = Quaternion::identity();
	Transform transform(position, orientation);

	RigidBody* body = world->createRigidBody(transform);
	rbStore.insert(std::make_pair(-1, body));
}

void Physics::AddRigidBody(GameObject go)
{
	Vector3 position(go.position.x, go.position.y, go.position.z);
	Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
	Transform transform(position, orientation);

	RigidBody* body = world->createRigidBody(transform);
	rbStore.emplace(go.GetID(), body);
}

void Physics::SetTimeStep(float time)
{
	timeStep = 1.0f / time;
}

void Physics::StepPhysics()
{
	world->update(timeStep);
}

void Physics::UpdateGO(GameObject go)
{
	for (std::map<int, RigidBody*>::iterator it = rbStore.begin(); it != rbStore.end(); ++it)
	{
		if (it->first == go.GetID())
		{
			//get and update position
			const Transform& transform = it->second->getTransform();
			const Vector3& position = transform.getPosition();

			go.position = glm::vec3(position.x, position.y, position.z);

			//get rotation							[NOT COMPLETE]
			const Quaternion& rotation = transform.getOrientation();
			
			//go.rotation = glm::vec3(0, 0, 0);  
		}
	}
}