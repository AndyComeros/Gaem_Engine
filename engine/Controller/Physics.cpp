#include <Physics.h>

void Physics::CreatePhysicsWorld()
{
	world = physicsCommon.createPhysicsWorld();
}

void Physics::DestroyPhysicsWorld()
{
	physicsCommon.destroyPhysicsWorld(world);
}

void Physics::AddGameObject(GameObject go)
{
	std::cout << go.GetID() << std::endl;
	goStore.emplace(go.GetID(), go);
}

void Physics::DelGameObject(int id)
{
	//delete record
	auto it = goStore.find(id);
	goStore.erase(it);
}

void Physics::AddRigidBody(GameObject go)
{
	Vector3 position(go.position.x, go.position.y, go.position.z);
	Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
	Transform transform(position, orientation);

	RigidBody* body = world->createRigidBody(transform);
	rbStore.emplace(go.GetID(), body);
}

void Physics::DelRigidBody(int id)
{
	//delete rb from simulation
	world->destroyRigidBody(rbStore[id]);

	//delete record
	auto it = rbStore.find(id);
	if (it != rbStore.end())
		rbStore.erase(it);
}

void Physics::AddRigidBodyColliderBox(int id, Vector3 scale)
{
	BoxShape* shape = physicsCommon.createBoxShape(scale);
	auto it = rbStore.find(id);
	if (it != rbStore.end())
	{
		Transform transform = Transform::identity();

		Collider* collider = it->second->addCollider(shape, transform);
		colStore.emplace(id, collider);
	}
}

void Physics::AddRigidBodyColliderSphere(int id, float radius)
{
	SphereShape* shape = physicsCommon.createSphereShape(radius);
	auto it = rbStore.find(id);
	if (it != rbStore.end())
	{
		Transform transform = Transform::identity();

		Collider* collider = it->second->addCollider(shape, transform);
		colStore.emplace(id, collider);
	}
}

void Physics::AddRigidBodyColliderCapsule(int id, float radius ,float height)
{
	CapsuleShape* shape = physicsCommon.createCapsuleShape(radius, height);
	auto it = rbStore.find(id);
	if (it != rbStore.end())
	{
		Transform transform = Transform::identity();

		Collider* collider = it->second->addCollider(shape, transform);
		colStore.emplace(id, collider);
	}
}

void Physics::AddRigidBodyColliderHeightMap(int id, float* heightValues[], int nbRows, int nbCols, float minH, float maxH)
{
	Vector3 scale = { 1,1,1 };
	HeightFieldShape* shape = physicsCommon.createHeightFieldShape(nbCols, nbRows, minH, maxH, heightValues, HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);

	auto it = rbStore.find(id);
	if (it != rbStore.end())
	{
		Transform transform = Transform::identity();

		Collider* collider = it->second->addCollider(shape, transform);
		colStore.emplace(id, collider);
	}
}

void Physics::AddColBody(GameObject go)
{
	Vector3 position(go.position.x, go.position.y, go.position.z);
	Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
	Transform transform(position, orientation);

	CollisionBody* body = world->createCollisionBody(transform);
	cbStore.emplace(go.GetID(), body);
}

void Physics::DelColBody(int id)
{
	//delete rb from simulation
	world->destroyCollisionBody(cbStore[id]);

	//delete record
	auto it = cbStore.find(id);
	cbStore.erase(it);
}

void Physics::ModRigidBodyType(int id, int type)
{
	auto it = rbStore.find(id);
	if (it != rbStore.end())
	{
		if (type == KINE)
			it->second->setType(BodyType::KINEMATIC);
		else if (type == STAT)
			it->second->setType(BodyType::STATIC);
		else if (type == DYNA)
			it->second->setType(BodyType::DYNAMIC);
	}
}

void Physics::ModRigidBodyGravity(int id, bool state)
{
	auto it = rbStore.find(id);
	if (it != rbStore.end())
		it->second->enableGravity(state);
}

void Physics::ApplyRigidBodyForce(int id, Vector3 force)
{
	auto it = rbStore.find(id);
	if (it != rbStore.end())
		it->second->applyLocalForceAtCenterOfMass(force);
}

void Physics::ApplyRigidBodyForce(int id, Vector3 force, Vector3 point)
{
	auto it = rbStore.find(id);
	if (it != rbStore.end())
		it->second->applyLocalForceAtLocalPosition(force, point);
}

void Physics::ApplyRigidBodyTorque(int id, Vector3 torque)
{
	auto it = rbStore.find(id);
	if (it != rbStore.end())
		it->second->applyLocalTorque(torque);
}

void Physics::SetTimeStep(float time)
{
	timeStep = 1.0f / time;
}

void Physics::StepPhysics()
{
	// timer
	long double currentFrameTime = glfwGetTime();
	mDeltaTime = currentFrameTime - previousFrameTime;
	previousFrameTime = currentFrameTime;
	accumulator += mDeltaTime;

	// While there is enough accumulated time to take one or several physics steps 
	while (accumulator >= timeStep)
	{
		// Update the Dynamics world with a constant time step 
		world->update(timeStep);
		 
		// Decrease the accumulated time 
		accumulator -= timeStep;
	}

	// update stores
	//UpdateCbStore();
	UpdateGoStore();
}

void Physics::UpdateCbStore()
{
	for (auto it : goStore)
	{
		auto ct = cbStore.find(it.first);
		if (ct != cbStore.end())
		{
			GameObject go = it.second;

			Vector3 position(go.position.x, go.position.y, go.position.z);
			Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
			Transform transform(position, orientation);

			ct->second->setTransform(transform);
		}
	}
}

void Physics::UpdateGoStore()
{
	for (auto it : rbStore)
	{
		auto gt = goStore.find(it.first);
		if (gt != goStore.end())
		{
			Transform transform = it.second->getTransform();
			Quaternion q = transform.getOrientation();

			gt->second.position = react2glm(transform.getPosition());
			gt->second.rotation = react2glm(transform.getOrientation().getVectorV());
		}
	}
}