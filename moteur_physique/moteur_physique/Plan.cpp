#include "Plan.h"

void Plan::Initialize(Vector3D _normal, float _offset)
{
	normal = _normal;
	offset = _offset;
}

Vector3D Plan::getNormal() const
{
	return normal;
}

float Plan::getPlaneOffset() const
{
	return offset;
}

void Plan::setNormal(Vector3D _normal)
{
	normal = _normal;
}

std::string Plan::getShape() const
{
	return "Plan";
}