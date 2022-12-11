#pragma once
#include "Primitive.h"
#include "Rotations/RigidBody.h"

class Sphere : public Primitive
{
public :
	float m_radius;

public:

	Sphere()
	{
		//nothing to be add here
	}

	void Initialize(float radius = 1, Vector3D offset = Vector3D(0, 0, 0));
	float getRadius();
	void setRadius(float radius);
};
