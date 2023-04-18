#include "Rigidbody.h"

void Rigidbody::ApplyForce(glm::vec3 force)
{
	if (!rbPtr)
		return;
	rbPtr->applyWorldForceAtCenterOfMass({force.x,force.y,force.z});
}

void Rigidbody::ModType(int type)
{
	switch (type)
	{
	case KINE:
		rbPtr->setType(rp3d::BodyType::KINEMATIC);
		break;
	case STAT:
		rbPtr->setType(rp3d::BodyType::STATIC);
		break;
	case DYNA:
		rbPtr->setType(rp3d::BodyType::DYNAMIC);
		break;
	}
}

void Rigidbody::SetUseGravity(bool isGravity)
{
	if (!rbPtr)
		return;
	rbPtr->enableGravity(isGravity);
}

void Rigidbody::SetPosition(glm::vec3 newPos)
{
	if (!rbPtr)
		return;
	rbPtr->setTransform(rp3d::Transform({ newPos.x,newPos.y,newPos.z }, rbPtr->getTransform().getOrientation()));
}

void Rigidbody::SetRotation(glm::vec3 newRot)
{
	if (!rbPtr)
		return;
	//convert to radians
	newRot = glm::radians(newRot);
	rp3d::Quaternion q;
	if (newRot.length() < std::numeric_limits<double>::epsilon()) {
		q = rp3d::Quaternion::identity();
	}
	else {
		q = rp3d::Quaternion::fromEulerAngles({ newRot.x,newRot.y,newRot.z });
	}
	q.normalize();
	rbPtr->setTransform(rp3d::Transform(rbPtr->getTransform().getPosition(),q));
}

glm::vec3 Rigidbody::GetPosition()
{
	if (!rbPtr)
		return glm::vec3();
	rp3d::Vector3 pos = rbPtr->getTransform().getPosition();
	return { pos.x,pos.y,pos.z };
}
