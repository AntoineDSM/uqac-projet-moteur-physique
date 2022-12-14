#pragma once

#ifndef PLAN
#define PLAN

#include "Primitive.h"
#include <Vector3D/Vector3D.h>


class Plan : public Primitive
{

public:

	Vector3D normal;
	float offset;

	//Constrcuteur par default
	Plan()
	{
		normal = Vector3D(0, 1, 0);
		offset = 0;
		m_offset = Matrix34();
		shape = "Plan";
	}

	void Initialize(Vector3D _normal, float _offset);

	//-----------------------------------------------------------GETTER & SETTER-------------------------------------------------------------------------------

	Vector3D getNormal() const;

	float getPlaneOffset() const;

	void setNormal(Vector3D normal);

	std::string getShape() const;

	//-----------------------------------------------------------------------------------------------------------------------------------------------------------
};

#endif PLAN