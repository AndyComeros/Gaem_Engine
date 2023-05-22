#pragma once
#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtc/matrix_transform.hpp>
//#include <glm/gtx/vector_angle.hpp>
//#include <glm/gtx/euler_angles.hpp>

struct Plane
{
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 normal = {0.0f,0.0f,0.0f};

	float CalcSignedDistance(glm::vec3& point)
	{
		return glm::dot(point - position, normal) / glm::length(normal);
	}
};

struct Frustum
{
	Plane top;
	Plane bottom;
	
	Plane left;
	Plane right;

	Plane far;
	Plane near;
};