#include "Sphere.h"

void Sphere::Initialize(float radius, Vector3D offset)
{
	radius = m_radius;
	shape.shape = "Sphere";
}

float Sphere::getRadius()
{
	return m_radius;
}

void Sphere::setRadius(float radius)
{
	m_radius = radius;
}