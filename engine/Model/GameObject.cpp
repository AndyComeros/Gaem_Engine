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
