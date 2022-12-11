#ifndef COLLISIONDATA_H
#define COLLISIONDATA_H

#pragma once
#include "Vector3D/Vector3D.h"
#include "Rotations/RigidBody.h"
#include "RigidBodyContact.h"
#include <vector>

class CollisionData
{
public:

	std::vector<RigidBodyContact*> contacts;

	int contactLeft;

	void addContact(int count)
	{
		contactLeft -= count;
	}
};

#endif COLLISIONDATA_H