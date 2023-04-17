#pragma once
#include <Physics.h>

class Rigidbody
{
public:
	void ApplyForce(glm::vec3 force);

	void AddColliderBox(Vector3 scale);
	void AddColliderSphere(float radius);
	void AddColliderCapsule(float radius, float height);

	void SetUseGravity(bool isGravity);
	void SetPosition(glm::vec3 newPos);

	void AddColliderHeightMap(Terrain& terrain);

	friend class Physics;
private:
	Rigidbody* rbPtr = nullptr;
};

