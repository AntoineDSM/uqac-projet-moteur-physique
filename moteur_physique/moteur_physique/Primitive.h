#pragma once
#include "Rotations/RigidBody.h"
#include "CollisionData.h"

class Primitive
{
	public:
		RigidBody* body;
		Matrix34 offset;

		void generateContact(const Primitive& Primi1, const Primitive& Primi2, CollisionData *data);
};