#pragma once
#include "Primitive.h"
#include <Vector3D/Vector3D.h>

class Plan : public Primitive
{
public:
	Vector3D m_normal;
	float m_planeOffset;

	Plan()
	{
		//nothing to be add here
	}

	void Initialize(Vector3D normal = Vector3D(0, 1, 0), Matrix34* offset = new Matrix34());
	const Vector3D getNormal() const;
	float getPlaneOffset() const;
	void setNormal(Vector3D normal);


	float getDistToPlane(Vector3D& point, const Plan& plan) {
		return  point.scalarProduct(plan.m_normal);
	}


};