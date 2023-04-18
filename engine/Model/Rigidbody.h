#pragma once
#include <reactphysics3d/reactphysics3d.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Physics;

class Rigidbody
{
public:
	void ApplyForce(glm::vec3 force);

	void ModType(GameObject& go, int type);

	void SetUseGravity(bool isGravity);
	void SetPosition(glm::vec3 newPos);



	glm::vec3 GetPosition();


	friend class Physics;
private:
	rp3d::RigidBody* rbPtr = nullptr;
};

