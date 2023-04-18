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
	if (nRot.y == 90)
		nRot.y = 89.9999;
	if (nRot.y == 270)
		nRot.y = 269.999;

	rigidBody.SetRotation(nRot);
	rotation = nRot;
}
