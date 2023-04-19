#include "GameObject.h"


GameObject::GameObject() {}

GameObject::~GameObject() {}

void GameObject::SetPosition(glm::vec3 nPos)
{
	rigidBody.SetPosition(nPos);
	position = nPos;
}

void GameObject::SetRotation(glm::vec3 nRot)
{
	rigidBody.SetRotation(nRot);
	rotation = nRot;
}

void GameObject::SetUpVec(glm::vec3 nUp)
{
	glm::vec3 targetPosition = glm::normalize(glm::cross(GetRightVec(), nUp));


	// Calculate the direction vector from the object to the target
	glm::vec3 directionVector = glm::normalize(targetPosition - position);

	// Calculate the angle between the object's facing direction and the target direction
	float angle = glm::acos(glm::dot(GetForwardVec(), directionVector));

	// Calculate the axis of rotation using the cross product of the two vectors
	glm::vec3 rotationAxis = glm::cross(GetForwardVec(), directionVector);

	// Create a rotation matrix using the angle and axis of rotation
	glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), angle, rotationAxis);

	// Apply the rotation to the object's facing direction
	glm::vec3 newForward = glm::vec3(rotationMatrix * glm::vec4(GetForwardVec(), 0.0f));

	glm::quat q = glm::quatLookAt(newForward, {0,1,0});

	SetRotation(glm::degrees(glm::eulerAngles(q)));

}

glm::vec3 GameObject::GetUpVec()
{
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	return glm::vec3(rotationMatrix[0][1], rotationMatrix[1][1], rotationMatrix[2][1]);
}

glm::vec3 GameObject::GetForwardVec()
{
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	return glm::vec3(rotationMatrix[0][2], rotationMatrix[1][2], rotationMatrix[2][2]);

}

glm::vec3 GameObject::GetRightVec()
{
	glm::mat4 rotationMatrix(1.0f);
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
	rotationMatrix = glm::rotate(rotationMatrix, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
	return glm::vec3(rotationMatrix[0][0], rotationMatrix[1][0], rotationMatrix[2][0]);
}
