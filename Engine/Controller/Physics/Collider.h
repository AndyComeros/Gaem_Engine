#pragma once
#include <glm/glm.hpp>

const int COLLIDER_INVALID	= 0;
const int COLLIDER_BOX		= 1;
const int COLLIDER_SPHERE	= 2;
const int COLLIDER_CAPSULE	= 3;
const int COLLIDER_TERRAIN	= 4;

struct PhysicsCollider
{
	PhysicsCollider() :
		mass(1),
		bounce(0.5),
		friction(0.3),
		offset({0,0,0}),
		rotation({0,0,0})
	{
		type = COLLIDER_INVALID;
	}

	float mass;
	float bounce;
	float friction;
	glm::vec3 offset;
	glm::vec3 rotation;

	int GetType() {
		return type;
	}

protected:
	int type;
};

struct BoxCollider : public PhysicsCollider
{
	BoxCollider() :
		scale({1,1,1})
	{
		type = COLLIDER_BOX;
	}
	glm::vec3 scale;
};

struct SphereCollider : public PhysicsCollider
{
	SphereCollider() :
		radius(0.5)
	{
		type = COLLIDER_SPHERE;
	}
	float radius;
};

struct CapsuleCollider : public PhysicsCollider
{
	CapsuleCollider() :
		radius(0.5),
		height(1)
	{
		type = COLLIDER_CAPSULE;
	}
	float radius;
	float height;
};

struct TerrainCollider : public PhysicsCollider
{
	TerrainCollider() :
		rows(0),
		columns(0),
		min(0),
		max(0),
		heights(nullptr)
	{
		type = COLLIDER_TERRAIN;
	}
	int rows;
	int columns;
	float min;
	float max;
	float* heights;
	
};