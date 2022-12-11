#pragma once

#ifndef COLLISION_DATA
#define COLLISION_DATA

#include "ContactRigidBody.h"

struct CollisionData 
{
	std::vector<ContactRigidBody*> contact = std::vector<ContactRigidBody*>();

	int contactLeft = 0;

	void addContact(int count)
	{
		contactLeft -= count;
	}
};

#endif COLLISION_DATA