#ifndef PLAN_H
#define PLAN_H
#pragma once
#include "Primitive.h"
#include <Vector3D/Vector3D.h>


class Plan : public Primitive
{
public:
	Vector3D normal;
	float offset;

	float getDistToPlane( Vector3D& point, const Plan& plan) {
		 return  point.scalarProduct(plan.normal);
	}


};

#endif