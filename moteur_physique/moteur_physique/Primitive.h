#pragma once
#include "Rotations/RigidBody.h"
#include "CollisionData.h"
#include "ShapeRB.h"

class Primitive
{
	public:
		RigidBody* body;
		Matrix34 offset;
		ShapeRB shape;

		Primitive()
		{
			//nothing to be add here
		}

		Primitive(RigidBody* _rb, Matrix34* _offset = new Matrix34())
		{
			body = _rb;
			shape = ShapeRB();
		}

		void setOffset(Matrix34* offset);
		void generateContact(const Primitive& Primi1, const Primitive& Primi2, CollisionData* data);
		
};