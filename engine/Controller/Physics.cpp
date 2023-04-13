#include <Physics.h>

void Physics::CreatePhysicsWorld()
{
	world = physicsCommon.createPhysicsWorld();
}

void Physics::DestroyPhysicsWorld()
{
	physicsCommon.destroyPhysicsWorld(world);
}

void Physics::AddRigidBody(GameObject &go)
{
	Vector3 position(go.position.x, go.position.y, go.position.z);
	Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
	Transform transform(position, orientation);
	go.rigidBody = world->createRigidBody(transform); 
}

void Physics::DelRigidBody(GameObject &go)
{
	//delete rb from simulation
	world->destroyRigidBody(go.rigidBody);
}

void Physics::AddRigidBodyColliderBox(GameObject &go, Vector3 scale)
{
	BoxShape* shape = physicsCommon.createBoxShape(scale);
	Transform transform = Transform::identity();

	go.rigidBody->addCollider(shape, transform); 
}

void Physics::AddRigidBodyColliderSphere(GameObject &go, float radius)
{
	SphereShape* shape = physicsCommon.createSphereShape(radius);
	Transform transform = Transform::identity();

	go.rigidBody->addCollider(shape, transform);
}

void Physics::AddRigidBodyColliderCapsule(GameObject &go, float radius ,float height)
{
	CapsuleShape* shape = physicsCommon.createCapsuleShape(radius, height);
	Transform transform = Transform::identity();

	go.rigidBody->addCollider(shape, transform);
}

void Physics::AddRigidBodyColliderHeightMap(GameObject &go, unsigned char* heightValues, int nbRows, int nbCols, float minH, float maxH)
{
	Vector3 scale = { 1,1,1 };
	HeightFieldShape* shape = physicsCommon.createHeightFieldShape(nbCols, nbRows, minH, maxH, heightValues, HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);

	Transform transform = Transform::identity();

	go.rigidBody->addCollider(shape, transform);
}

void Physics::ModRigidBodyType(GameObject &go, int type)
{
	switch (type)
	{
	case KINE:
		go.rigidBody->setType(BodyType::KINEMATIC);
		break;
	case STAT:
		go.rigidBody->setType(BodyType::STATIC);
		break;
	case DYNA:
		go.rigidBody->setType(BodyType::DYNAMIC);
		break;
	}
}

void Physics::ModRigidBodyGravity(GameObject &go, bool state)
{
	go.rigidBody->enableGravity(state);
}

void Physics::ApplyRigidBodyForce(GameObject &go, Vector3 force)
{
	go.rigidBody->applyLocalForceAtCenterOfMass(force);
}

void Physics::ApplyRigidBodyForce(GameObject &go, Vector3 force, Vector3 point)
{
	go.rigidBody->applyLocalForceAtLocalPosition(force, point);
}

void Physics::ApplyRigidBodyTorque(GameObject &go, Vector3 torque)
{
	go.rigidBody->applyLocalTorque(torque);
}

void Physics::updateGameObjects(std::vector<GameObject>& goStore)
{
	//UPDATE GO POSITON
	for (int i = 0; i < goStore.size(); i++) 
	{
		Transform transform = goStore[i].rigidBody->getTransform();
		Vector3 position = transform.getPosition();

		goStore[i].position = glm::vec3(position.x, position.y, position.z);
	}	
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

	if (DispDebug)				// TEMP TEMP TEMP TEMP REMOVE LATER PLS
		DebugDisplay();

}

void Physics::DebugDisplay()
{
	// Enable debug rendering 
	world->setIsDebugRenderingEnabled(true);

	// Get a reference to the debug renderer 
	DebugRenderer& debugRenderer = world->getDebugRenderer();

	// Select the contact points and contact normals to be displayed 
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_POINT, true);
	debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_NORMAL, true);

	int nLines = debugRenderer.getNbLines();
	int nTri = debugRenderer.getNbTriangles();
	const reactphysics3d::DebugRenderer::DebugLine *line = debugRenderer.getLinesArray();
	const reactphysics3d::DebugRenderer::DebugTriangle *tri = debugRenderer.getTrianglesArray();

	/*
	glColor3f(1, 0, 0 );
	glBegin(GL_LINES);
	for (int i = 0; i < nLines; ++i) {
		const reactphysics3d::DebugRenderer::DebugLine& debugLine = line[i];
		glVertex3f(debugLine.point1.x, debugLine.point1.y, debugLine.point1.z);
		glVertex3f(debugLine.point2.x, debugLine.point2.y, debugLine.point2.z);
	}
	glEnd();

	glBegin(GL_TRIANGLES);
	for (int i = 0; i < nTri; ++i) {
		const reactphysics3d::DebugRenderer::DebugTriangle& debugTri = tri[i];
		glVertex3f(debugTri.point1.x, debugTri.point1.y, debugTri.point1.z);
		glVertex3f(debugTri.point2.x, debugTri.point2.y, debugTri.point2.z);
		glVertex3f(debugTri.point3.x, debugTri.point3.y, debugTri.point3.z);
	}
	glEnd();*/
}