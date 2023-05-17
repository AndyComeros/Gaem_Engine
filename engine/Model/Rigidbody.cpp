#include "Rigidbody.h"

void Rigidbody::ApplyForce(glm::vec3 force)
{
	if (!rbPtr)
		return;
	rbPtr->applyWorldForceAtCenterOfMass({force.x,force.y,force.z});
}

void Rigidbody::ApplyForceLocal(glm::vec3 force)
{
	if (!rbPtr)
		return;
	rbPtr->applyLocalForceAtCenterOfMass({ force.x,force.y,force.z });
}

void Rigidbody::ApplyTorqueLocal(glm::vec3 torque)
{
	if (!rbPtr)
		return;
	rbPtr->applyLocalTorque({ torque.x, torque.y, torque.z });
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

void Rigidbody::SetMass(float nMass)
{
	if (!rbPtr)
		return;
	rbPtr->setMass(nMass);
}

void Rigidbody::SetCenterOfMass(glm::vec3 center)
{
	if (!rbPtr)
		return;
	rbPtr->setLocalCenterOfMass({ center.x, center.y, center.z });
}

void Rigidbody::SetDampeningLinear(float damp)
{
	if (!rbPtr)
		return;
	rbPtr->setLinearDamping(damp);
}

void Rigidbody::SetDampeningAngle(float damp)
{
	if (!rbPtr)
		return;
	rbPtr->setAngularDamping(damp);
}

void Rigidbody::SetAxisLinearFactor(float x, float y, float z)
{
	if (!rbPtr)
		return;
	rbPtr->setLinearLockAxisFactor({ x,y,z });
}

void Rigidbody::SetAxisAngleFactor(float x, float y, float z)
{
	if (!rbPtr)
		return;
	rbPtr->setAngularLockAxisFactor({ x,y,z });
}

glm::vec3 Rigidbody::GetLinearVelocty()
{
	if (!rbPtr)
		return glm::vec3(0);

	rp3d::Vector3 rVal = rbPtr->getLinearVelocity();

	return { rVal.x,rVal.y,rVal.z };
}

glm::vec3 Rigidbody::GetAngularVelocity()
{
	if (!rbPtr)
		return glm::vec3(0);

	rp3d::Vector3 rVal = rbPtr->getAngularVelocity();

	return { rVal.x,rVal.y,rVal.z};
}