#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <ResourceManager.h>
#include <map>
#include <math.h>
#include <algorithm>
#include <glm/gtx/euler_angles.hpp>

using namespace reactphysics3d;



class Physics
{
public:
	Physics();
	~Physics();

	void CreatePhysicsWorld();
	void DestroyPhysicsWorld();

	//add and del rigidbodies
	void AddRigidBody(GameObject &go, int rbType);
	void DelRigidBody(GameObject &go);

	//modify rigidbodies
	void ModRigidBodyType(GameObject &go, int rbType);
	void ModRigidBodyGravity(GameObject &go, bool state);	// true == on

	//apply force to rigidbodies
	void ApplyRigidBodyForce(GameObject &go, Vector3 force);
	void ApplyRigidBodyForce(GameObject &go, Vector3 force, Vector3 point);
	void ApplyRigidBodyTorque(GameObject &go, Vector3 torque);

	//add and del rigidbody colliders
	void AddRigidBodyColliderBox(GameObject &go, glm::vec3 scale,float mass, float bounce, float friction);
	void AddRigidBodyColliderSphere(GameObject &go, float radius, glm::vec3 offset, float mass, float bounce, float friction);
	void AddRigidBodyColliderCapsule(GameObject& go, float radius, float height, glm::vec3 offset, glm::vec3 rotation, float mass, float bounce, float friction);
	//TODO add Model3D to convex function
	//TODO add Model3D to concave function
	void AddRigidBodyColliderHeightMap(Terrain &terrain);

	//setter and getter
	void SetRigidBodyPosition(GameObject &go, Vector3 newPos);
	Vector3 GetRigidBodyPosition(GameObject& go);

	//ray casting
	//TODO add Ray casting

	//update GO vector
	void UpdateGameObjects(std::map<std::string, GameObject*>& goStore);

	//simulation settings
	void SetTimeStep(float time);
	void StepPhysics(float deltaTime);					

	//misc
	inline glm::vec3 react2glm(const Vector3& vec){return { vec.x, vec.y, vec.z };}
	inline Vector3 glm2react(glm::vec3& vec) { return {vec.x, vec.y, vec.z}; }
	void ToggleDebugDisplay();

	//display debug 
	void DrawDebug(Camera* cam, Shader* shader);
private:
	//physics factory and world
	PhysicsCommon physicsCommon;	
	PhysicsWorld* world;

	Model* debug_model = nullptr;

	//updates per second
	decimal timeStep = 0.0f;
	float accumulator = 0.0f;

	bool isDebug = false;
};

