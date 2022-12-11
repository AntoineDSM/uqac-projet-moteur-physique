#include "Plan.h"

void Plan::Initialize(Vector3D normal, Matrix34* offset)
{
	m_normal = normal;
	setOffset(offset);
	shape.shape = "Plan";
}

const Vector3D Plan::getNormal() const
{
	return m_normal;
}

void Plan::setNormal(Vector3D normal)
{
	m_normal = normal;
}

float Plan::getPlaneOffset() const
{
	return m_planeOffset;
}

