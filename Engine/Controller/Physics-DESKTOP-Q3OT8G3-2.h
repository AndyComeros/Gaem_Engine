#pragma once

#include "../Model/GameObject.h"
#include <../Dependancies/bullet/btBulletDynamicsCommon.h>

class Physics
{
public:
	static Physics& getInstance() {  //singleton
		static Physics instance;
		return instance;
	}

	void SetupPhysWorld();
	void AddRigidBody(GameObject go);
private:
	Physics() {}
	Physics(Physics const&);

	btDiscreteDynamicsWorld* worldPhys;
};

