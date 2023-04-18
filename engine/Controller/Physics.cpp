#include <Physics.h>

Physics::Physics() {
	CreatePhysicsWorld();
	SetTimeStep(60);
}

Physics::~Physics() {
	DestroyPhysicsWorld();
}

void Physics::CreatePhysicsWorld()
{
	world = physicsCommon.createPhysicsWorld();
}

void Physics::DestroyPhysicsWorld()
{
	physicsCommon.destroyPhysicsWorld(world);
}

void Physics::AddRigidBody(GameObject &go, int rbType)
{
	Vector3 position(go.position.x, go.position.y, go.position.z);
	Quaternion orientation = Quaternion::fromEulerAngles((float)go.rotation.x, (float)go.rotation.y, (float)go.rotation.z);
	Transform transform(position, orientation);

	go.rigidBody.rbPtr = world->createRigidBody(transform);

	ModRigidBodyType(go,rbType);
}

void Physics::DelRigidBody(GameObject &go)
{
	//delete rb from simulation
	world->destroyRigidBody(go.rigidBody.rbPtr);
}

void Physics::AddRigidBodyColliderBox(GameObject &go, Vector3 scale)
{
	BoxShape* shape = physicsCommon.createBoxShape(scale);
	Transform transform = Transform::identity();

	go.rigidBody.rbPtr->addCollider(shape, transform); 
}

void Physics::AddRigidBodyColliderSphere(GameObject &go, float radius)
{
	SphereShape* shape = physicsCommon.createSphereShape(radius);
	Transform transform = Transform::identity();

	go.rigidBody.rbPtr->addCollider(shape, transform);
}

void Physics::AddRigidBodyColliderCapsule(GameObject &go, float radius ,float height)
{
	CapsuleShape* shape = physicsCommon.createCapsuleShape(radius, height);
	Transform transform = Transform::identity();

	go.rigidBody.rbPtr->addCollider(shape, transform);
}

void Physics::AddRigidBodyColliderHeightMap(Terrain& terrain)
{
	int rows = terrain.GetSize();
	int cols = terrain.GetSize();
	float min = terrain.GetMinHeight();
	float max = terrain.GetMaxHeight();
	float* hv = &terrain.GetHeightArray()->at(0);
	HeightFieldShape* shape = physicsCommon.createHeightFieldShape(rows, cols, min, max, hv, HeightFieldShape::HeightDataType::HEIGHT_FLOAT_TYPE);
	shape->setScale({terrain.GetScaleX(),1,terrain.GetScaleZ()});
	Transform transform = Transform::identity();
	terrain.rigidBody.rbPtr->addCollider(shape, transform);
}

void Physics::ModRigidBodyType(GameObject &go, int type)
{
	switch (type)
	{
	case KINE:
		go.rigidBody.rbPtr->setType(BodyType::KINEMATIC);
		break;
	case STAT:
		go.rigidBody.rbPtr->setType(BodyType::STATIC);
		break;
	case DYNA:
		go.rigidBody.rbPtr->setType(BodyType::DYNAMIC);
		break;
	}
}

void Physics::ModRigidBodyGravity(GameObject &go, bool state)
{
	go.rigidBody.rbPtr->enableGravity(state);
}

void Physics::ApplyRigidBodyForce(GameObject &go, Vector3 force)
{
	go.rigidBody.rbPtr->applyLocalForceAtCenterOfMass(force);
}

void Physics::ApplyRigidBodyForce(GameObject &go, Vector3 force, Vector3 point)
{
	go.rigidBody.rbPtr->applyLocalForceAtLocalPosition(force, point);
}

void Physics::ApplyRigidBodyTorque(GameObject &go, Vector3 torque)
{
	go.rigidBody.rbPtr->applyLocalTorque(torque);
}

void Physics::SetRigidBodyPosition(GameObject &go, Vector3 newPos)
{
	Quaternion quat = Quaternion::identity();
	Transform transform(newPos, quat);
	go.rigidBody.rbPtr->setTransform(transform);
}

Vector3 Physics::GetRigidBodyPosition(GameObject& go)
{
	Transform transform = go.rigidBody.rbPtr->getTransform();
	Vector3 vec = transform.getPosition();
	return vec;
}

void Physics::UpdateGameObjects(std::map<std::string, GameObject>& goStore)
{
	for (auto& it : goStore) {
		
		if (it.second.rigidBody.rbPtr) {
			Transform transform = it.second.rigidBody.rbPtr->getTransform();
			Vector3 position = transform.getPosition();
			it.second.position = glm::vec3(position.x, position.y, position.z);
		}

	}
}

void Physics::SetTimeStep(float time)
{
	timeStep = 1.0f / time;
}

void Physics::StepPhysics(float deltaTime)
{
	accumulator += deltaTime;

	// While there is enough accumulated time to take one or several physics steps 
	if (accumulator >= timeStep && timeStep > 0)
	{
		// Update the Dynamics world with a constant time step 
		world->update(timeStep);
		// Decrease the accumulated time 
		accumulator -= timeStep;
	}
}

void Physics::DrawDebug(Camera* cam, Shader* shader)
{
	if (isDebug) {
		// Enable debug rendering 
		world->setIsDebugRenderingEnabled(true);
		// Get a reference to the debug renderer 
		DebugRenderer& debugRenderer = world->getDebugRenderer();
		// Select the contact points and contact normals to be displayed 
		debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_POINT, true);
		debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::CONTACT_NORMAL, true);
		debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLISION_SHAPE, true);
		debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLIDER_AABB, true);
		debugRenderer.setIsDebugItemDisplayed(DebugRenderer::DebugItem::COLLIDER_BROADPHASE_AABB, true);
		int nLines = debugRenderer.getNbLines();
		int nTri = debugRenderer.getNbTriangles();

		if (nTri > 0) {

			glDisable(GL_CULL_FACE);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			//set model matrix uniforms
			glm::mat4 modelMat(1.0f);
			
			const reactphysics3d::DebugRenderer::DebugTriangle* tri = debugRenderer.getTrianglesArray();

			if (debug_model)
				debug_model->FreeData();

			debug_model = new Model();
			shader->SetUniform("model", modelMat);

			debug_model->SetDebugVertexData((float*)&tri->point1.x, nTri * 3);
			debug_model->Render(cam, shader, false, GL_TRIANGLES);
			
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_CULL_FACE);
			glCullFace(GL_BACK);
		}
	
	}
	
}