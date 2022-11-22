#ifndef PLAN_H
#define PLAN_H
#pragma once
#include "Primitive.h"


class Plan : public Primitive
{
public:
	Vector3D normal;
	float offset;

};

#endif