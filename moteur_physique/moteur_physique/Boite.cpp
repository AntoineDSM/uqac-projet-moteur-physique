#include "Boite.h"

void Boite::Initialize(Vector3D halfSize, Matrix34* offset)
{
	m_halfSize = halfSize;
	setOffset(offset);
	shape.shape = "Boite";
}

Vector3D Boite::getHalfSize()
{
	return m_halfSize;
}

void Boite::setHalfSize(Vector3D halfSize)
{
	m_halfSize = halfSize;
}

const Vector3D& Boite::getVertex(int i) const
{
	return vertices[i];
}
